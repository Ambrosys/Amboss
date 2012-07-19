/*
 * GeometryTest.cpp
 *
 *  Created on: 19.06.2012
 *      Author: karsten
 */

#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#include "TestingPoint.h"


using namespace std;
using namespace Amboss::KML;


TEST( KMLGeometry , defaultConstruction )
{
    Geometry e;
}

TEST( KMLGeometry , valueConstruction )
{
    TestingPoint p;
    Geometry e( p );
}

TEST( KMLGeometry , copyConstruction )
{
    Geometry e1;
    Geometry e2( e1 );

    TestingPoint p;
    Geometry e3( p );
    Geometry e4( e3 );
}

TEST( KMLGeometry , copying )
{
    Geometry e1;
    Geometry e2;
    e2 = e1;

    TestingPoint p1 , p2;
    Geometry e3( p1 );
    Geometry e4( p2 );
    e3 = e4;
}

TEST( KMLGeometry , oneTestingPoint )
{
    Geometry e( TestingPoint( 10.0 , 10.0 ) );
    ostringstream str;
    e.write( str , 0 );
	
    string cmp = 
        "<Point>\n"
        "  <coordinates>\n"
        "    10,10,0 \n"
        "  </coordinates>\n"
        "</Point>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLGeometry , twoTestingPoint )
{
    Geometry e1( TestingPoint( 10.0 , 10.0 ) );
    Geometry e2( TestingPoint( 5.0 , 5.0 ) );
    e2 = e1;
    ostringstream str;
    e2.write( str , 0 );
	
    string cmp = 
        "<Point>\n"
        "  <coordinates>\n"
        "    10,10,0 \n"
        "  </coordinates>\n"
        "</Point>\n";

    EXPECT_EQ( cmp , str.str() );
}



