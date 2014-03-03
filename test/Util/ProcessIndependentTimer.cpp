/*
 * test/Util/ProcessIndependentTimer.cpp
 * Date: 2014-03-03
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <Amboss/Util/ProcessIndependentTimer.h>
#include <gtest/gtest.h>

#include <sstream>
#include <chrono>
#include <thread>

#define TESTNAME ProcessIndependentTimer

using namespace std;
using namespace Amboss::Util;

void f()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

TEST( TESTNAME , TestCase )
{
    ProcessIndependentTimer timer;
    f();
    double seconds = timer.seconds();
    
    EXPECT_GT( seconds , 1.4 );
    EXPECT_LT( seconds , 1.6 );
}
