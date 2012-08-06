/*
 * Sqlite3DB.cpp
 * Date: 2012-08-06
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/Sqlite3/Sqlite3DB.h>

using namespace std;
using namespace Amboss::Sqlite3;

TEST( TestName , TestCase )
{
    Sqlite3DB db( "abc.db" );
    EXPECT_EQ( true , true );
}
