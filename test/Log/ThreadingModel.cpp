/*
 * ThreadingModel.cpp
 * Date: 2013-05-28
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <Amboss/Log/ThreadingModel.h>

#include <gtest/gtest.h>

#include <sstream>
#include <thread>

using namespace std;
using namespace Amboss::Log;

typedef MultiThreadModel ThreadingModel ;
ThreadingModel m;

void func1( std::ostream &out )
{
    std::lock_guard< ThreadingModel > lock( m );
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    out << "func1\n" << flush;
}

void func2( std::ostream &out )
{
    std::lock_guard< ThreadingModel > lock( m );
    out << "func2\n" << flush;
}

TEST( ThreadingModel , test1 )
{
    std::ostringstream str;
    std::thread t( func1 , std::ref( str ) );
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    func2( str );
    t.join();

    EXPECT_EQ( str.str() , "func1\nfunc2\n" );
}
