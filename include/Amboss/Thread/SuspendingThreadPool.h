/*
 * SuspendingThreadPool.h
 * Date: 2013-07-08
 * Author: Fabian Sandoval Saldias (fabianvss@gmail.com)
 * Copyright: Fabian Sandoval Saldias
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * 
 * This class is based on Karsten Ahnert's ThreadPool.h.
 */

#ifndef AMBOSS_SUSPENDING_THREAD_POOL_H_INCLUDED
#define AMBOSS_SUSPENDING_THREAD_POOL_H_INCLUDED


#include <Amboss/Thread/FunctionWrapper.h>
#include <Amboss/Util/AmbossException.h>

#include <vector>
#include <queue>
#include <thread>
#include <future>


namespace Amboss {
namespace Thread {

    class SuspendingThreadPool
    {
    public:

        typedef FunctionWrapper task_type;
    
        SuspendingThreadPool( size_t threadCount = std::thread::hardware_concurrency() )
        {
            for( size_t i=0; i<threadCount; ++i )
                threads_.push_back( std::thread( &SuspendingThreadPool::worker_thread, this ) );
        }
        
        /// Late initialization, needed e.g. for CppCMS as daemon (otherwise threads don't wake up)
        void lateInit( size_t threadCount = std::thread::hardware_concurrency() )
        {
            std::lock_guard<std::mutex> mutexLocker( mutex_ );
            if ( threads_.size() == 0 ) {
                for( size_t i=0; i<threadCount; ++i )
                    threads_.push_back( std::thread( &SuspendingThreadPool::worker_thread, this ) );
            }
        }

        ~SuspendingThreadPool()
        {
            mutex_.lock();
            done_ = true;
            condition_.notify_all();
            mutex_.unlock();
            for( auto &thread : threads_ )
                thread.join();
        }

        template<typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type>
        submit( FunctionType f )
        {
            typedef typename std::result_of<FunctionType()>::type ResultType;

            if( threadCount() == 0 ) throw Amboss::Util::AmbossException( "FastThreadPool::submit() : no threads present." );

            std::packaged_task<ResultType()> task( std::move( f ) );
            std::future<ResultType> res( task.get_future() );

            std::lock_guard<std::mutex> mutexLocker( mutex_ );
            workQueue_.push( std::move( task ) );
            condition_.notify_all();
            return res;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> mutexLocker( mutex_ );
            return workQueue_.empty() && !working_;
        }

        size_t pending() const
        {
            std::lock_guard<std::mutex> mutexLocker( mutex_ );
            return workQueue_.size() + working_;
        }

        size_t threadCount() const { return threads_.size(); }

        void waitUntilFinished()
        {
            std::unique_lock<std::mutex> mutexLocker( mutex_ );
            notifyWhenFinished_ = true;
            while( !workQueue_.empty() || working_ )
                condition_.wait( mutexLocker );
            notifyWhenFinished_ = false;
        }

    private:

        void worker_thread()
        {
            std::unique_lock<std::mutex> mutexLocker( mutex_ );
            while( !done_ )
            {
                if( !workQueue_.empty() )
                {
                    task_type task = std::move( workQueue_.front() );
                    workQueue_.pop();
                    working_++;
                    mutexLocker.unlock();
                    task();
                    mutexLocker.lock();
                    working_--;
                }
                else
                {
                    if( notifyWhenFinished_ && !working_ )
                        condition_.notify_all();
                    condition_.wait( mutexLocker );
                }
            }
        }

        bool done_ { false };
        bool notifyWhenFinished_ { false };
        size_t working_ { 0 };
        std::queue<task_type> workQueue_;
        std::vector<std::thread> threads_;

        mutable std::mutex mutex_;
        std::condition_variable condition_;

    };

} // namespace Thread
} // namespace Amboss 


#endif // AMBOSS_SUSPENDING_THREAD_POOL_H_INCLUDED
