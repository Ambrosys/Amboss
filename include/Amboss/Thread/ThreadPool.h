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
 * This class is strongly inspired from Anthony William's "C++ Concurrency in Action".
 */

#ifndef AMBOSS_THREAD_POOL_H_INCLUDED
#define AMBOSS_THREAD_POOL_H_INCLUDED

#include <Amboss/Thread/ThreadSafeQueue.h>
#include <Amboss/Thread/FunctionWrapper.h>
#include <Amboss/Util/AmbossException.h>

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
        : done_( false ) , numberRunning_( 0 ) , workQueue_() , threads_() 
    {
        try
        {
            for( size_t i=0 ; i<threadCount ; ++i )
            {
                threads_.push_back( std::thread( &ThreadPool::worker_thread , this ) );
            }
        }
        catch( ... )
        {
            done_ = true;
            throw Amboss::Util::AmbossException { "" };
        }
    }
    
    ~ThreadPool()
    {
        done_ = true;
        for( auto &thread : threads_ )
        {
            if( thread.joinable() ) thread.join();
        }
    }

    template< typename FunctionType >
    std::future< typename std::result_of< FunctionType() >::type >
    submit( FunctionType f )
    {
        typedef typename std::result_of< FunctionType() >::type ResultType;
        
        if( threadCount() == 0 ) throw Amboss::Util::AmbossException( "ThreadPool::submit() : no threads present." );

        std::packaged_task< ResultType() > task( std::move( f ) );
        std::future< ResultType > res( task.get_future() );
        workQueue_.push( std::move( task ) );
        return res;
    }

    bool empty( void ) const { return workQueue_.empty(); }

    size_t pending( void ) const { return workQueue_.size(); }
    
    size_t threadCount( void ) const { return threads_.size(); }
    
    size_t runningThreads() const { return numberRunning_; }

    /// check whether jobs in queue or threads still running
    bool busy() const
    {
        return !empty() || numberRunning_ > 0;
    }
    
    /// Wait until all submitted jobs are finished
    void waitUntilFinished()
    {
        while ( busy() ) 
            std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );        
    }

private:

    void worker_thread()
    {
        while( !done_ )
        {
            task_type task;
            if( workQueue_.tryPop( task ) )
            {
                ++numberRunning_;
                task();
                --numberRunning_;
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }


    std::atomic_bool             done_;
    std::atomic_uint             numberRunning_;
    ThreadSafeQueue< task_type > workQueue_;
    std::vector< std::thread >   threads_;
};

} // namespace Thread
} // namespace Amboss 


#endif // AMBOSS_THREAD_POOL_H_INCLUDED
