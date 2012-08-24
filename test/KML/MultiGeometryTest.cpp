/*
 * MultiGeometryTest.cpp
 * Date: 2012-08-24
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/KML/MultiGeometry.h>
#include "TestingPoint.h"


using namespace std;
using namespace Amboss::KML;


TEST( KMLMultiGeometry , defaultConstruction )
{
    MultiGeometry e;
}

TEST( KMLMultiGeometry , add )
{
    MultiGeometry mg;
    mg.add( TestingPoint( 1.0 , 1.0 ) );
}

TEST( KMLMultiGeometry , oneGeometry )
{
    MultiGeometry mg;
    mg.add( TestingPoint( 10.0 , 10.0 ) );
    ostringstream str;

    Geometry e( mg );
    e.write( str , 0 );
	
    string cmp = 
        "<MultiGeometry>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</MultiGeometry>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLMultiGeometry , copyConstruction )
{
    MultiGeometry mg;
    mg.add( TestingPoint( 10.0 , 10.0 ) );

    MultiGeometry mg2( mg );
    Geometry e( mg2 );
	
    string cmp = 
        "<MultiGeometry>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</MultiGeometry>\n";

    ostringstream str;
    e.write( str , 0 );
    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLMultiGeometry , assignment )
{
    MultiGeometry mg;
    mg.add( TestingPoint( 10.0 , 10.0 ) );

    MultiGeometry mg2;
    mg2 = mg;
    Geometry e( mg2 );
	
    string cmp = 
        "<MultiGeometry>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</MultiGeometry>\n";

    ostringstream str;
    e.write( str , 0 );
    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLMultiGeometry , twoGeometries )
{
    MultiGeometry mg;
    mg.add( TestingPoint( 10.0 , 10.0 ) );
    mg.add( TestingPoint( 20.0 , 20.0 ) );

    string cmp = 
        "<MultiGeometry>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      10,10,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      20,20,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</MultiGeometry>\n";

    ostringstream str;
    Geometry e( mg );
    e.write( str , 0 );
    EXPECT_EQ( cmp , str.str() );
}
