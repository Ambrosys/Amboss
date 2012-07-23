/*
 * ColorStyleTest.cpp
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

#include <Amboss/KML/Styles/ColorStyle.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLColorStyle , testConstruction )
{
    ColorStyle cs1;
    ColorStyle cs2( Color( 255 , 255 , 255 ) );
    ColorStyle cs3( White );
    ColorStyle cs4( Color( 255 , 255 , 255 ) , ColorStyle::normal );
    ColorStyle cs5( White , ColorStyle::random );
}

TEST( KMLColorStyle , testWrite1 )
{
    ColorStyle cs( Red , ColorStyle::normal );
    std::ostringstream str;
    cs.write( str , 0 );
    std::string cmp =
        "<color>ff0000ff</color>\n"
        "<colorMode>normal</colorMode>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLColorStyle , testWrite2 )
{
    ColorStyle cs( Blue , ColorStyle::random );
    std::ostringstream str;
    cs.write( str , 0 );
    std::string cmp =
        "<color>ffff0000</color>\n"
        "<colorMode>random</colorMode>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLColorStyle , testEq )
{
    ColorStyle cs1( Blue , ColorStyle::random );
    ColorStyle cs2( cs1 );
    EXPECT_EQ( cs1 , cs2 );

    ColorStyle cs3;
    cs3.color() = Blue;
    cs3.colorMode() = ColorStyle::random;
    EXPECT_EQ( cs1 , cs3 );
   
    cs3.color() = Yellow;
    EXPECT_NE( cs1 , cs3 );
}
