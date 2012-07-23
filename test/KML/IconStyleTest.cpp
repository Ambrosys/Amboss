/*
 * IconStyleTest.cpp
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

#include <Amboss/KML/Styles/IconStyle.h>

using namespace std;
using namespace Amboss::KML;

TEST( KMLIconStyle , testConstruction )
{
    IconStyle is1;
    EXPECT_FALSE( bool( is1 ) );
    IconStyle is2( White , 1.0 , "" );
    EXPECT_TRUE( bool( is2 ) );
    IconStyle is3( White , 1.0 , PushPin );
    EXPECT_TRUE( bool( is3 ) );
}

TEST( KMLIconStyle , testSetColor )
{
    IconStyle is;
    is.colorStyle() = White;
    EXPECT_TRUE( bool( is ) );
    EXPECT_EQ( is.colorStyle() , ColorStyle( White ) );
}

TEST( KMLIconStyle , testSetScale )
{
    IconStyle is;
    is.scale() = 2.55;
    EXPECT_TRUE( bool( is ) );
    EXPECT_DOUBLE_EQ( is.scale() , 2.55 );
}

TEST( KMLIconStyle , testSetIconRef )
{
    IconStyle is;
    is.setIconRef( PushPin );
    EXPECT_TRUE( bool( is ) );
    EXPECT_EQ( is.iconRef() , "http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png" );

    IconStyle is2;
    is2.iconRef() = "icon";
    EXPECT_TRUE( bool( is2 ) );
    EXPECT_EQ( is2.iconRef() , "icon" );
}

TEST( KMLIconStyle , testReset )
{
    IconStyle is;
    is.colorStyle() = White;
    is.reset();
    EXPECT_FALSE( bool( is ) );
}


TEST( KMLIconStyle , testEmptyWrite )
{
    IconStyle is;
    std::ostringstream str;
    is.write( str , 1 );
    EXPECT_EQ( str.str() , "" );
}

TEST( KMLIconStyle , testWrite )
{
    IconStyle is( Green , 2.2 , PushPin );
    std::ostringstream str;
    is.write( str , 0 );
    std::string cmp = 
        "<IconStyle>\n"
        "  <color>ff00ff00</color>\n"
        "  <colorMode>normal</colorMode>\n"
        "  <scale>2.2</scale>\n"
        "  <Icon><href>http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png</href></Icon>\n"
        "</IconStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}

TEST( KMLIconStyle , testWrite2 )
{
    IconStyle is( Green , 2.2 , PushPin );
    std::ostringstream str;
    is.write( str , 1 );
    std::string cmp = 
        "  <IconStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>2.2</scale>\n"
        "    <Icon><href>http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png</href></Icon>\n"
        "  </IconStyle>\n";
    EXPECT_EQ( str.str() , cmp );
}
