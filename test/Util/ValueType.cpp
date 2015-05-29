/*
 * ValueType.cpp
 * Date: 2012-08-14
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#define AMB_DEBUG 1

#include <sstream>
#include <utility>
#include <iostream>

#include <gtest/gtest.h>

#include <Amboss/Util/ValueType.h>
#include <Amboss/Util/AmbossException.h>

using namespace std;
using namespace Amboss::Util;



TEST( ValueType , testDefaultConstructor )
{
    ValueType v;
    EXPECT_TRUE( v.empty() );
}

TEST( ValueType , testValueConstructor )
{
    std::string a = "Hello";
    ValueType v( a );
    EXPECT_FALSE( v.empty() );
    EXPECT_TRUE( v.sameType< std::string >() );
    EXPECT_NO_THROW({
            EXPECT_EQ( v.as< std::string >() , "Hello" );
        });
    EXPECT_THROW({ int a = v.as< int >(); } , AmbossException );
    EXPECT_NO_THROW({
            int a = v.as( 10 );
            EXPECT_EQ( a , 10 );
        });
}

TEST( ValueType , testValueMoveConstructor )
{
    std::string a = "Hello";
    ValueType v( std::move( a ) );
    EXPECT_FALSE( v.empty() );
    EXPECT_TRUE( v.sameType< std::string >() );
    EXPECT_NO_THROW({
            EXPECT_EQ( v.as< std::string >() , "Hello" );
        });
    EXPECT_EQ( a , "" );
    // EXPECT_THROW({ int a = v.as< int >(); } , AmbossException );
    // EXPECT_NO_THROW({
    //         int a = v.as( 10 );
    //         EXPECT_EQ( a , 10 );
    //     });
}


TEST( ValueType , testCopyConstructor )
{
    std::string a = "Hello";
    ValueType v1( a );
    ValueType v2( v1 );
    EXPECT_TRUE( v1.sameType( v2 ) );
    EXPECT_FALSE( v1.empty() );
    EXPECT_FALSE( v2.empty() );
    EXPECT_TRUE( v1.sameType< std::string >() );
    EXPECT_TRUE( v1.sameType< std::string >() );
    EXPECT_NO_THROW({
            EXPECT_EQ( v1.as< std::string >() , "Hello" );
            EXPECT_EQ( v2.as< std::string >() , "Hello" );
        });
}

TEST( ValueType , testValueAssignment )
{
    std::string a = "Hello";
    ValueType v( a );
    v = 10;
    EXPECT_FALSE( v.empty() );
    EXPECT_TRUE( v.sameType< int >() );
    EXPECT_NO_THROW({
            EXPECT_EQ( v.as< int >() , 10 );
        });
}

TEST( ValueType , testCopyAssignment )
{
    std::string a = "Hello";
    ValueType v1( a );
    ValueType v2( 10 );
    EXPECT_FALSE( v1.sameType( v2 ) );
    v2 = v1;
    EXPECT_TRUE( v1.sameType( v2 ) );
    EXPECT_FALSE( v1.empty() );
    EXPECT_FALSE( v2.empty() );
    EXPECT_TRUE( v1.sameType< std::string >() );
    EXPECT_TRUE( v1.sameType< std::string >() );
    EXPECT_NO_THROW({
            EXPECT_EQ( v1.as< std::string >() , "Hello" );
            EXPECT_EQ( v2.as< std::string >() , "Hello" );
        });
}
