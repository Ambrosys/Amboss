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
#include <Amboss/Util/AmbossException.h>

#include "Sqlite3TestConfig.h"

using namespace std;
using namespace Amboss::Sqlite3;
using namespace Amboss::Util;

TEST( Sqlite3 , testDefaultConstructor )
{
    EXPECT_NO_THROW(
        {
            Sqlite3DB db;
        });
}

TEST( Sqlite3 , testConstructionFromFile )
{
    EXPECT_NO_THROW(
        {
            Sqlite3DB db( AMBOSS_SQLITE_SAMPLE_DB );
            Sqlite3DB::ResultType res = db.query( "SELECT * FROM testtable" );
            EXPECT_EQ( res.size() , 1 );
            EXPECT_EQ( res[0].size() , 1 );
            EXPECT_EQ( res[0][0] , "test1" );
        });

    EXPECT_THROW(
        {
            Sqlite3DB db( "dir/abc.db" );
        } , AmbossException );
}

TEST( Sqlite3 , testOpen )
{
    EXPECT_NO_THROW(
        {
            Sqlite3DB db;
            db.open( AMBOSS_SQLITE_SAMPLE_DB );
            Sqlite3DB::ResultType res = db.query( "SELECT * FROM testtable" );
            EXPECT_EQ( res.size() , 1 );
            EXPECT_EQ( res[0].size() , 1 );
            EXPECT_EQ( res[0][0] , "test1" );
        });

    EXPECT_THROW(
        {
            Sqlite3DB db;
            db.open(  "dir/abc.db"  );
        } , AmbossException );
}

TEST( Sqlite3 , testClose )
{
    EXPECT_THROW(
        {
            Sqlite3DB db( AMBOSS_SQLITE_SAMPLE_DB );
            db.close();
            Sqlite3DB::ResultType res = db.query( "SELECT * FROM testtable" );
        } , AmbossException );
}
