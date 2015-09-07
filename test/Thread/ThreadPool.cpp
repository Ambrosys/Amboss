/*
 * ThreadPool.cpp
 * Date: 2012-08-14
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#define AMB_DEBUG 1

#include <Amboss/Thread/ThreadPool.h>
#include <Amboss/Thread/SuspendingThreadPool.h>

#include <sstream>
#include <utility>
#include <iostream>

#include <gtest/gtest.h>



using namespace std;
using namespace Amboss::Thread;

void func_void( void ) {   }
double func_double( void ) {  return 1.0; }
long long func_sleep( void ) { usleep( 1000/100 * (rand() % 100) ); return 1; }

struct Moveable
{
    Moveable( void ) = default;
    Moveable( Moveable const & ) = delete;
    Moveable( Moveable && ) = default;
    
    
    Moveable& operator=( Moveable const & ) = delete;
    Moveable& operator=( Moveable && ) = default;
    
    void operator()( void ) const { double a = 1.0; a *= 2.0; }
};


int main( int argc, char **argv )
{
    testing::InitGoogleTest( &argc, argv );
    srand( 0 );
    return RUN_ALL_TESTS();
}


TEST( ThreadPool , testDefaultConstructor )
{
    ThreadPool pool();
}

TEST( ThreadPool , testConstructor )
{
    ThreadPool pool( 4 );
    EXPECT_EQ( pool.threadCount() , 4 );
}


TEST( ThreadPool , testPoolWithVoidFunction )
{
    ThreadPool pool( 4 );
    auto f = pool.submit( func_void );
    f.get();
}

TEST( ThreadPool , testPoolWithDoubleFunction )
{
    ThreadPool pool( 4 );
    auto f = pool.submit( func_double );
    double res = f.get();
    EXPECT_DOUBLE_EQ( 1.0 , res );
}

TEST( ThreadPool , testPoolWithMoveableFunction1 )
{
    Moveable m;
    ThreadPool pool( 4 );
    pool.submit( std::move( m ) );
}

TEST( ThreadPool , testSuspendableThreadPool1 )
{
    int const numTasks = 100;
    int const numThreads = 4;
    SuspendingThreadPool pool( numThreads );
    typedef std::future<long long> Future;
    std::vector<Future> futures;
    for( int i = 0; i < numTasks; i++ )
        futures.push_back( pool.submit( func_sleep ) );
    long long result = 0;
    for( auto &future : futures )
        result += future.get();
    EXPECT_EQ( result, numTasks );
}

TEST( ThreadPool , testSuspendableThreadPool2 )
{
    class ThreadSafeIncrementor
    {
    public:
        void increment( long long v ) { std::unique_lock<std::mutex> mutexLocker( mutex_ ); value_ += v; }
        long long value() const       { std::unique_lock<std::mutex> mutexLocker( mutex_ ); return value_; }
    private:
        mutable std::mutex mutex_;
        long long value_ = 0;
    };

    class Helper
    {
    public:
        static void threadFunction( SuspendingThreadPool &pool, int const tasks, ThreadSafeIncrementor &incrementor )
        {
            typedef std::future<long long> Future;
            std::vector<Future> futures;
            for( int i = 0; i < tasks; i++ )
                futures.push_back( pool.submit( func_sleep ) );
            for( auto &future : futures )
                incrementor.increment( future.get() );
        }
    };

    int const iterations = 10*100/100;
    int const numTasks = 32*4;
    int const numThreads = 8*4;

    ThreadSafeIncrementor incrementor;

    SuspendingThreadPool pool( numTasks );
    for( int i = 0; i < iterations; i++ )
    {
        std::vector<std::thread> threads;
        for( int j = 0; j < numThreads; j++ )
            threads.push_back( std::thread( std::bind( Helper::threadFunction, std::ref( pool ), numTasks, std::ref( incrementor ) ) ) );
        for( auto &thread : threads )
            thread.join();
    }
    EXPECT_EQ( incrementor.value(), (long long)iterations * numTasks * numThreads );
}


TEST( ThreadPool , testPropagateException )
{
    struct dummy_exception : public std::runtime_error { using std::runtime_error::runtime_error; };
    
    ThreadPool pool;
    auto fut = pool.submit( []( void ) { std::this_thread::sleep_for( std::chrono::milliseconds( 800 ) ); throw dummy_exception{ "Dummy error" }; } );
    EXPECT_THROW( fut.get() , dummy_exception );
}
