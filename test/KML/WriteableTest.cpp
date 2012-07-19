/*
 * WriteableTest.cpp
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


TEST( KMLWriteable , defaultConstruction )
{
    Writeable e;
}

TEST( KMLWriteable , valueConstruction )
{
    TestingPoint p;
    Writeable e( p );
}

TEST( KMLWriteable , copyConstruction )
{
    Writeable e1;
    Writeable e2( e1 );

    TestingPoint p;
    Writeable e3( p );
    Writeable e4( e3 );
}

TEST( KMLWriteable , copying )
{
    Writeable e1;
    Writeable e2;
    e2 = e1;

    TestingPoint p1 , p2;
    Writeable e3( p1 );
    Writeable e4( p2 );
    e3 = e4;
}

TEST( KMLWriteable , oneTestingPoint )
{
    Writeable e( TestingPoint( 10.0 , 10.0 ) );
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

TEST( KMLWriteable , twoTestingPoint )
{
    Writeable e1( TestingPoint( 10.0 , 10.0 ) );
    Writeable e2( TestingPoint( 5.0 , 5.0 ) );
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



