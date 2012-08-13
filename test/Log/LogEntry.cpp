/*
 * LogEntry.cpp
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/Log/LogEntry.h>

using namespace std;
using namespace Amboss::Log;

TEST( LogEntry , testMakeLogEntry )
{
    LogEntry l;
    EXPECT_NO_THROW({
            l = makeLogEntry( INFO , "message" , "filename" , 23 );
        });

    EXPECT_EQ( l.logLevel , INFO );
    EXPECT_EQ( l.message , "message" );
    EXPECT_EQ( l.filename , "filename" );
    EXPECT_EQ( l.lineNumber , 23 );
}
