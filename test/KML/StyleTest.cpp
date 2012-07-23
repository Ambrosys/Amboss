/*
 * StyleTest.cpp
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

#include <Amboss/KML/Style.h>

using namespace std;
using namespace Amboss::KML;


TEST( KMLStyle , testConstruction )
{
    Style s1;
    EXPECT_FALSE( bool( s1 ) );

    Style s2( "id" );
    EXPECT_TRUE( bool( s2 ) );

    Style s3( IconStyle( White ) );
    EXPECT_TRUE( bool( s3 ) );
}

TEST( KMLStyle , testSetId )
{
    Style s;
    s.id() = "Id";
    EXPECT_EQ( s.id() , "Id" );
    EXPECT_TRUE( bool( s ) );
}

TEST( KMLStyle , testSetIconStyle )
{
    Style s;
    s.iconStyle() = IconStyle( White );
    EXPECT_TRUE( bool( s ) );
    EXPECT_EQ( s.iconStyle() , IconStyle( White ) );
}

TEST( KMLStyle , testSetLineStyle )
{
    Style s;
    s.lineStyle() = LineStyle( White );
    EXPECT_TRUE( bool( s ) );
    EXPECT_EQ( s.lineStyle() , LineStyle( White ) );
}

TEST( KMLStyle , testSetPolyStyle )
{
    Style s;
    s.polyStyle() = PolyStyle( White );
    EXPECT_TRUE( bool( s ) );
    EXPECT_EQ( s.polyStyle() , PolyStyle( White ) );
}

TEST( KMLStyle , testSetLabelStyle )
{
    Style s;
    s.labelStyle() = LabelStyle( White );
    EXPECT_TRUE( bool( s ) );
    EXPECT_EQ( s.labelStyle() , LabelStyle( White ) );
}

TEST( KMLStyle , testWriteEmpty )
{
    Style s;
    std::ostringstream str;
    s.write( str , 4 );
    EXPECT_EQ( str.str() , "" );
}   


TEST( KMLStyle , testWrite1 )
{
    Style s;
    s.iconStyle() = IconStyle( Green , 2.2 , PushPin );
    s.lineStyle() = LineStyle( Yellow , 2.2 );
    s.polyStyle() = PolyStyle( Green );
    s.labelStyle() = LabelStyle( Green , 1.25 );
    std::ostringstream str;
    s.write( str , 0 );
    std::string cmp = 
        "<Style>\n"
        "  <IconStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>2.2</scale>\n"
        "    <Icon><href>http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png</href></Icon>\n"
        "  </IconStyle>\n"
        "  <LineStyle>\n"
        "    <color>ff00ffff</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <width>2.2</width>\n"
        "  </LineStyle>\n"
        "  <PolyStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <fill>1</fill>\n"
        "    <outline>1</outline>\n"
        "  </PolyStyle>\n"
        "  <LabelStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>1.25</scale>\n"
        "  </LabelStyle>\n"
        "</Style>\n";
    EXPECT_EQ( str.str() , cmp );
}


TEST( KMLStyle , testWrite2 )
{
    Style s;
    s.iconStyle() = IconStyle( Green , 2.2 , PushPin );
    s.lineStyle() = LineStyle( Yellow , 2.2 );
    s.polyStyle() = PolyStyle( Green );
    s.labelStyle() = LabelStyle( Green , 1.25 );
    std::ostringstream str;
    s.write( str , 1 );
    std::string cmp = 
        "  <Style>\n"
        "    <IconStyle>\n"
        "      <color>ff00ff00</color>\n"
        "      <colorMode>normal</colorMode>\n"
        "      <scale>2.2</scale>\n"
        "      <Icon><href>http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png</href></Icon>\n"
        "    </IconStyle>\n"
        "    <LineStyle>\n"
        "      <color>ff00ffff</color>\n"
        "      <colorMode>normal</colorMode>\n"
        "      <width>2.2</width>\n"
        "    </LineStyle>\n"
        "    <PolyStyle>\n"
        "      <color>ff00ff00</color>\n"
        "      <colorMode>normal</colorMode>\n"
        "      <fill>1</fill>\n"
        "      <outline>1</outline>\n"
        "    </PolyStyle>\n"
        "    <LabelStyle>\n"
        "      <color>ff00ff00</color>\n"
        "      <colorMode>normal</colorMode>\n"
        "      <scale>1.25</scale>\n"
        "    </LabelStyle>\n"
        "  </Style>\n";
    EXPECT_EQ( str.str() , cmp );
}


TEST( KMLStyle , testWrite3 )
{
    Style s;
    s.id() = "id";
    s.iconStyle() = IconStyle( Green , 2.2 , PushPin );
    s.lineStyle() = LineStyle( Yellow , 2.2 );
    s.polyStyle() = PolyStyle( Green );
    s.labelStyle() = LabelStyle( Green , 1.25 );
    std::ostringstream str;
    s.write( str , 0 );
    std::string cmp = 
        "<Style id=\"id\">\n"
        "  <IconStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>2.2</scale>\n"
        "    <Icon><href>http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png</href></Icon>\n"
        "  </IconStyle>\n"
        "  <LineStyle>\n"
        "    <color>ff00ffff</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <width>2.2</width>\n"
        "  </LineStyle>\n"
        "  <PolyStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <fill>1</fill>\n"
        "    <outline>1</outline>\n"
        "  </PolyStyle>\n"
        "  <LabelStyle>\n"
        "    <color>ff00ff00</color>\n"
        "    <colorMode>normal</colorMode>\n"
        "    <scale>1.25</scale>\n"
        "  </LabelStyle>\n"
        "</Style>\n";
    EXPECT_EQ( str.str() , cmp );
}


TEST( KMLStyle , testEq )
{
    Style s1;
    s1.id() = "id";
    s1.iconStyle() = IconStyle( Green , 2.2 , PushPin );
    s1.lineStyle() = LineStyle( Yellow , 2.2 );
    s1.polyStyle() = PolyStyle( Green );
    s1.labelStyle() = LabelStyle( Green , 1.25 );

    Style s2( s1 );
    EXPECT_EQ( s1 , s2 );

    Style s3;
    s3 = s1;
    EXPECT_EQ( s1 , s3 );

    Style s4;
    s4.id() = "id";
    s4.iconStyle() = IconStyle( Green , 2.2 , PushPin );
    s4.lineStyle() = LineStyle( Yellow , 2.2 );
    s4.polyStyle() = PolyStyle( Green );
    s4.labelStyle() = LabelStyle( Green , 1.25 );
    EXPECT_EQ( s1 , s4 );
    
    s4.id() = "id2";
    EXPECT_NE( s1 , s4 );
}
