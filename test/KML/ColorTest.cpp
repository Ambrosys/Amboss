/*
 * ColorTest.cpp
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/KML/Styles/Color.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLColor , testDefaultConstruction )
{
    Color c;
}

TEST( KMLColor , testConstruction )
{
    Color c1( 0x23 , 0xf6 , 0x08 , 0x12 );
    EXPECT_EQ( c1.red() , 0x23 );
    EXPECT_EQ( c1.green() , 0xf6 );
    EXPECT_EQ( c1.blue() , 0x08 );
    EXPECT_EQ( c1.alpha() , 0x12 );

    Color c2( 0x23 , 0xf6 , 0x08  );
    EXPECT_EQ( c2.red() , 0x23 );
    EXPECT_EQ( c2.green() , 0xf6 );
    EXPECT_EQ( c2.blue() , 0x08 );
    EXPECT_EQ( c2.alpha() , 0xff );
}

TEST( KMLColor , testConstructionFromDefaultColors )
{
    Color white( White );
    EXPECT_EQ( white.red() , 0 );
    EXPECT_EQ( white.green() , 0 );
    EXPECT_EQ( white.blue() , 0 );
    EXPECT_EQ( white.alpha() , 255 );

    Color black( Black );
    EXPECT_EQ( black.red() , 255 );
    EXPECT_EQ( black.green() , 255 );
    EXPECT_EQ( black.blue() , 255 );
    EXPECT_EQ( black.alpha() , 255 );

    Color red( Red );
    EXPECT_EQ( red.red() , 255 );
    EXPECT_EQ( red.green() , 0 );
    EXPECT_EQ( red.blue() , 0 );
    EXPECT_EQ( red.alpha() , 255 );

    Color green( Green );
    EXPECT_EQ( green.red() , 0 );
    EXPECT_EQ( green.green() , 255 );
    EXPECT_EQ( green.blue() , 0 );
    EXPECT_EQ( green.alpha() , 255 );

    Color blue( Blue );
    EXPECT_EQ( blue.red() , 0 );
    EXPECT_EQ( blue.green() , 0 );
    EXPECT_EQ( blue.blue() , 255 );
    EXPECT_EQ( blue.alpha() , 255 );

    Color yellow( Yellow );
    EXPECT_EQ( yellow.red() , 255 );
    EXPECT_EQ( yellow.green() , 255 );
    EXPECT_EQ( yellow.blue() , 0 );
    EXPECT_EQ( yellow.alpha() , 255 );

 
}

TEST( KMLColor , testSet )
{
    Color c;
    c.red() =  65;
    EXPECT_EQ( c.red() , 65 );
    c.green() = 63;
    EXPECT_EQ( c.green() , 63 );
    c.blue() = 64;
    EXPECT_EQ( c.blue() , 64 );
    c.alpha() = 62;
    EXPECT_EQ( c.alpha() , 62 );
}

TEST( KMLColor , testWrite )
{
    Color c( 255 , 255 , 255 );
    EXPECT_EQ( c.kmlString() , "ffffffff" );

    Color c2( 0x23 , 0xf6 , 0x08 , 0x12 );
    EXPECT_EQ( c2.kmlString() , "1208f623" );
}

TEST( KMLColor , testEq )
{
    Color c1( 123 , 122 , 121 , 233 );
    Color c2( 123 , 122 , 121 , 233 );
    EXPECT_EQ( c1 , c2 );

    Color c3( c1 );
    EXPECT_EQ( c1 , c3 );

    Color c4;
    c4 = c1;
    EXPECT_EQ( c1 , c4 );

    c4.red() = 124;
    EXPECT_NE( c1 , c4 );
}
