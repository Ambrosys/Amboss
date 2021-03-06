/*
 * ThreadSafeQueue.h
 * Date: 2013-04-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_THREAD_SAFE_QUEUE_H_INCLUDED
#define AMBOSS_THREAD_SAFE_QUEUE_H_INCLUDED

#include <queue> 
#include <memory>
#include <mutex>
#include <condition_variable>

namespace Amboss {
namespace Thread {

template<typename T>
class ThreadSafeQueue
{
public:

    ThreadSafeQueue( void )
    {}

    void push( T new_value )
    {
        std::lock_guard< std::mutex > lk( mutex_ );
        dataQueue_.push( std::move( new_value ) );
        dataCond_.notify_one();
    }

    bool tryPop( T& value )
    {
        std::lock_guard< std::mutex > lk( mutex_ );
        if( dataQueue_.empty() )
            return false;
        value = std::move( dataQueue_.front() );
        dataQueue_.pop();
        return true;
    }

    std::shared_ptr<T> tryPop( void )
    {
        std::lock_guard< std::mutex > lk( mutex_ );
        if( dataQueue_.empty() )
            return std::shared_ptr<T>();
        std::shared_ptr<T> res( std::make_shared<T>( std::move( dataQueue_.front() ) ) );
        dataQueue_.pop();
        return res;
    }

    bool empty( void ) const
    {
        std::lock_guard< std::mutex > lk( mutex_ );
        return dataQueue_.empty();
    }

    size_t size( void ) const
    {
        std::lock_guard< std::mutex > lk( mutex_ );
        return dataQueue_.size();
    }

private:

    mutable std::mutex mutex_;
    std::queue<T> dataQueue_;
    std::condition_variable dataCond_;

};

} // namespace Thread
} // namespace Amboss

#endif // AMBOSS_THREAD_SAFE_QUEUE_H_INCLUDED
