/*
 * CompletingThreadPool.h
 * Author: Peter Gottschling
 * Copyright: Peter Gottschling
 * 
 */

#ifndef AMBOSS_COMPLETING_THREAD_POOL_H_INCLUDED
#define AMBOSS_COMPLETING_THREAD_POOL_H_INCLUDED

#include <Amboss/Thread/ThreadPool.h>

#include <thread>
#include <chrono>

namespace Amboss {
namespace Thread {

/// Thread pool that completes all threads in desctructor (when going out of scope)
class CompletingThreadPool : public ThreadPool
{
public:
    using ThreadPool::ThreadPool;
    
    ~CompletingThreadPool()
    {
        while ( !empty() )
            std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );        
    }  
};
        

} // namespace Thread
} // namespace Amboss 


#endif // AMBOSS_COMPLETING_THREAD_POOL_H_INCLUDED
