/*
 * ThreadPool.h
 * Date: 2013-04-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * 
 * This class is strongly inspired from Anthony Williams "C++ Concurrency in Action".
 */

#ifndef AMBOSS_THREAD_POOL_H_INCLUDED
#define AMBOSS_THREAD_POOL_H_INCLUDED



#include <Amboss/Thread/ThreadSafeQueue.h>
#include <Amboss/Thread/FunctionWrapper.h>
#include <Amboss/Thread/ThreadJoiner.h>

#include <vector>
#include <thread>
#include <future>

namespace Amboss {
namespace Thread {



class ThreadPool
{
public:

    typedef FunctionWrapper task_type;

    ThreadPool( size_t threadCount = std::thread::hardware_concurrency() )
        : done_( false ) , workQueue_() , threads_() , joiner_( threads_ ) ,
          mutex_() , startCondition_()
    {
        try
        {
            for( size_t i=0 ; i<threadCount ; ++i )
            {
                threads_.push_back( std::thread( &ThreadPool::worker_thread , this ) );

                std::unique_lock< std::mutex > lk( mutex_ );
                startCondition_.wait( lk );
            }
        }
        catch( ... )
        {
            done_ = true;
            throw;
        }
    }
    
    ~ThreadPool()
    {
        done_ = true;
    }

    template< typename FunctionType >
    std::future< typename std::result_of< FunctionType() >::type >
    submit( FunctionType &&f )
    {
        typedef typename std::result_of< FunctionType() >::type ResultType;
        
        if( threadCount() == 0 ) throw std::runtime_error( "ThreadPool::submit() : no threads present." );

        std::packaged_task< ResultType() > task( std::move( f ) );
        std::future< ResultType > res( task.get_future() );
        workQueue_.push( std::move( task ) );
        return res;
    }

    bool empty( void ) const { return workQueue_.empty(); }

    size_t pending( void ) const { return workQueue_.size(); }
    
    size_t threadCount( void ) const { return threads_.size(); }


private:

    void worker_thread()
    {
        startCondition_.notify_one();
        while( !done_ )
        {
            task_type task;
            if( workQueue_.tryPop( task ) )
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }


    std::atomic_bool done_;
    ThreadsafeQueue< task_type > workQueue_;
    std::vector< std::thread > threads_;
    ThreadJoiner joiner_;

    std::mutex mutex_;
    std::condition_variable startCondition_;

};

} // namespace Thread
} // namespace Amboss 


#endif // AMBOSS_THREAD_POOL_H_INCLUDED
