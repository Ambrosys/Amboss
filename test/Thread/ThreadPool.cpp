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

#include <sstream>
#include <utility>
#include <iostream>

#include <gtest/gtest.h>



using namespace std;
using namespace Amboss::Thread;

void func1( void ) {   }
double func2( void ) {  return 1.0; }


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
    auto f = pool.submit( func1 );
    f.get();
}

TEST( ThreadPool , testPoolWithDoubleFunction )
{
    ThreadPool pool( 4 );
    auto f = pool.submit( func2 );
    double res = f.get();
    EXPECT_DOUBLE_EQ( 1.0 , res );
}