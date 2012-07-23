/*
 * LineStyleTest.cpp
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

#include <Amboss/KML/Styles/LineStyle.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLLineStyle , testConstruction )
{
    LineStyle ls;
    EXPECT_FALSE( bool( ls ) );

    LineStyle ls2( White , 2.2 );
    EXPECT_TRUE( bool( ls2 ) );
}

TEST( KMLLineStyle , testSetColor )
{
    LineStyle ls;
    ls.colorStyle() = Blue;
    EXPECT_TRUE( bool( ls ) );
    EXPECT_EQ( ls.colorStyle() , ColorStyle( Blue , ColorStyle::normal ) );
}

TEST( KMLineStyle , testSetWidth )
{
    LineStyle ls;
    ls.width() = 2.4;
    EXPECT_TRUE( bool( ls ) );
    EXPECT_DOUBLE_EQ( ls.width() , 2.4 );
}

TEST( KMLLineStyle , testReset )
{
    LineStyle ls;
    ls.colorStyle() = White;
    ls.reset();
    EXPECT_FALSE( bool( ls ) );
}

TEST( KMLLineStyle , testEmptyWrite )
{
    LineStyle ls;
    std::ostringstream str;
    ls.write( str , 4 );
    EXPECT_EQ( str.str() , "" );
}

TEST( KMLLineStyle , testWrite1 )
{
    LineStyle ls( Yellow , 2.2 );
    std::ostringstream str;
    ls.write( str , 0 );
    std::string cmp =
        "<LineStyle>\n"
        "  <color>ffffff00</color>\n"
        "  <colorMode>normal</colorMode>\n"
        "  <width>2.2</width>\n"
        "</LineStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLLineStyle , testWrite2 )
{
    LineStyle ls( Yellow , 2.2 );
    std::ostringstream str;
    ls.write( str , 1 );
    std::string cmp =
        "  <LineStyle>\n"
        "    <color>ffffff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <width>2.2</width>\n"
        "  </LineStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}




