/*
 * LabelStyleTest.cpp
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

#include <Amboss/KML/Styles/LabelStyle.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLLabelStyle , testConstruction )
{
    LabelStyle ls1;
    EXPECT_FALSE( bool( ls1 ) );
    LabelStyle ls2( White );
    EXPECT_TRUE( bool( ls2 ) );
}

TEST( KMLLabelStyle , testSetColor )
{
    LabelStyle ls;
    ls.colorStyle() = White;
    EXPECT_TRUE( bool( ls ) );
    EXPECT_EQ( ls.colorStyle() , ColorStyle( White ) );
}

TEST( KMLLabelStyle , testSetScale )
{
    LabelStyle ls;
    ls.scale() = 2.55;
    EXPECT_TRUE( bool( ls ) );
    EXPECT_DOUBLE_EQ( ls.scale() , 2.55 );
}


TEST( KMLLabelStyle , testReset )
{
    LabelStyle ls;
    ls.colorStyle() = White;
    ls.reset();
    EXPECT_FALSE( bool( ls ) );
}


TEST( KMLLabelStyle , testEmptyWrite )
{
    LabelStyle ls;
    std::ostringstream str;
    ls.write( str , 1 );
    EXPECT_EQ( str.str() , "" );
}

TEST( KMLLabelStyle , testWrite1 )
{
    LabelStyle ls( Green , 1.25 );
    std::ostringstream str;
    ls.write( str , 0 );
    std::string cmp = 
        "<LabelStyle>\n"
        "  <color>ff00ff00</color>\n"
        "  <colorMode>normal</colorMode>\n"
        "  <scale>1.25</scale>\n"
        "</LabelStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLLabelStyle , testWrite2 )
{
    LabelStyle ls( Green , 1.25 );
    std::ostringstream str;
    ls.write( str , 1 );
    std::string cmp = 
        "  <LabelStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>1.25</scale>\n"
        "  </LabelStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLLabelStyle , testEq )
{
    LabelStyle is1;
    LabelStyle is2;
    EXPECT_EQ( is1 , is2 );

    LabelStyle is3( White , 4.0 );
    LabelStyle is4( White , 4.0 );
    EXPECT_EQ( is3 , is4 );
    is4.reset();
    EXPECT_NE( is3 , is4 );
    is4.scale() = 3.0;
    EXPECT_NE( is3 , is4 );

    LabelStyle is5 = is3;
    EXPECT_EQ( is3 , is5 );
}
