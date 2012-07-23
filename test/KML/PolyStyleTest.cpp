/*
 * PolyStyleTest.cpp
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

#include <Amboss/KML/Styles/PolyStyle.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLPolyStyle , testConstruction )
{
    PolyStyle ps1;
    EXPECT_FALSE( bool( ps1 ) );
    PolyStyle ps2( White );
    EXPECT_TRUE( bool( ps2 ) );
    PolyStyle ps3( White , true );
    EXPECT_TRUE( bool( ps3 ) );
    PolyStyle ps4( White , true , false );
    EXPECT_TRUE( bool( ps4 ) );
}

TEST( KMLPolyStyle , testSetColor )
{
    PolyStyle ps;
    ps.colorStyle() = White;
    EXPECT_TRUE( bool( ps ) );
    EXPECT_EQ( ps.colorStyle() , ColorStyle( White ) );
}

TEST( KMLPolyStyle , testSetFill )
{
    PolyStyle ps;
    ps.fill() = false;
    EXPECT_TRUE( bool( ps ) );
    EXPECT_EQ( ps.fill() , false );
}

TEST( KMLPolyStyle , testSetOutline )
{
    PolyStyle ps;
    ps.outline() = false;
    EXPECT_TRUE( bool( ps ) );
    EXPECT_EQ( ps.outline() , false );
}



TEST( KMLPolyStyle , testReset )
{
    PolyStyle ps;
    ps.colorStyle() = White;
    ps.reset();
    EXPECT_FALSE( bool( ps ) );
}


TEST( KMLPolyStyle , testEmptyWrite )
{
    PolyStyle ps;
    std::ostringstream str;
    ps.write( str , 1 );
    EXPECT_EQ( str.str() , "" );
}

TEST( KMLPolyStyle , testWrite1 )
{
    PolyStyle ps( Green );
    std::ostringstream str;
    ps.write( str , 0 );
    std::string cmp = 
        "<PolyStyle>\n"
        "  <color>ff00ff00</color>\n"
        "  <colorMode>normal</colorMode>\n"
        "  <fill>1</fill>\n"
        "  <outline>1</outline>\n"
        "</PolyStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLPolyStyle , testWrite2 )
{
    PolyStyle ps( Green );
    std::ostringstream str;
    ps.write( str , 1 );
    std::string cmp = 
        "  <PolyStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <fill>1</fill>\n"
        "    <outline>1</outline>\n"
        "  </PolyStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLPolyStyle , testEq )
{
    PolyStyle is1;
    PolyStyle is2;
    EXPECT_EQ( is1 , is2 );

    PolyStyle is3( White , true , false );
    PolyStyle is4( White , true , false );
    EXPECT_EQ( is3 , is4 );
    is4.reset();
    EXPECT_NE( is3 , is4 );
    is4.fill() = false ;
    EXPECT_NE( is3 , is4 );

    PolyStyle is5 = is3;
    EXPECT_EQ( is3 , is5 );
}
