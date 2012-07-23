/*
 * PlacemarkTest.cpp
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <Amboss/KML/Placemark.h>

#include "TestingPoint.h"

#include <gtest/gtest.h>

using namespace std;
using namespace Amboss::KML;


TEST( KMLPlacemark , defaultConstruction )
{
    Placemark p;
}

TEST( KMLPlacemark , copyConstruction )
{
    Placemark p;
    Placemark p1( p );
}

TEST( KMLPlacemark , assignment )
{
    Placemark p1;
    Placemark p2;
    p2 = p1;
}

TEST( KMLPlacemark , constructFromGeom )
{
    Placemark p1( TestingPoint( 10.0 , 10.0 ) );
    Placemark p2( TestingPoint( 10.0 , 10.0 ) , "Placemark" );
}

TEST( KMLPlacemark , constructionWithStyle )
{
    Placemark p1( TestingPoint( 10.0 , 10.0 ) , Style( "id" ) );
    Placemark p2( TestingPoint( 10.0 , 10.0 ) , Style( "id" ) , "Placemark" );
    EXPECT_FALSE( p1.styles().empty() );
    EXPECT_FALSE( p2.styles().empty() );
    EXPECT_EQ( p1.styles().front() , Style( "id" ) );
    EXPECT_EQ( p2.styles().front() , Style( "id" ) );
}


TEST( KMLPlacemark , writePoint )
{
    Placemark p( TestingPoint( 10.0 , 10.0 ) );
    ostringstream str;
    writeFeature( str , p , 0 );

	
    string cmp = 
        "<Placemark>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Placemark>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLPlacemark , writePointAndName )
{
    Placemark p( TestingPoint( 10.0 , 10.0 ) , "Placemark" );
    ostringstream str;
    writeFeature( str , p , 0 ); // other version of write
	
    string cmp = 
        "<Placemark>\n"
        "  <name>Placemark</name>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Placemark>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLPlacemark , writePointAndNameAndStyle )
{
    Placemark p( TestingPoint( 10.0 , 10.0 ) , Style( "id" ) , "Placemark" );
    ostringstream str;
    writeFeature( str , p , 0 ); // other version of write
	
    string cmp = 
        "<Placemark>\n"
        "  <name>Placemark</name>\n"
        "  <Style id=\"id\">\n"
        "  </Style>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Placemark>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLPlacemark , writePointAndNameAndStyleUrl )
{
    Placemark p( TestingPoint( 10.0 , 10.0 ) , "Placemark" );
    p.urls().push_back( "link" );
    ostringstream str;
    writeFeature( str , p , 0 ); // other version of write
	
    string cmp = 
        "<Placemark>\n"
        "  <name>Placemark</name>\n"
        "  <StyleUrl>link</StyleUrl>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Placemark>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLPlacemark , setName )
{
    Placemark p;
    p.name() = "hi";
    EXPECT_EQ( p.name() , "hi" );
}

TEST( KMLPlacemark , setGeometry )
{
    Placemark p;
    p.geometry() = TestingPoint( 10.0 , 10.0 );
    ostringstream str;
    writeFeature( str , p , 0 );
	
    string cmp = 
        "<Placemark>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Placemark>\n";

    EXPECT_EQ( cmp , str.str() );
}
