/*
 * WriterTest.cpp
 *
 *  Created on: 19.06.2012
 *      Author: karsten
 */

#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#include <Amboss/KML/WriterHelper.h>
#include <Amboss/KML/Writer.h>

#include "TestingPoint.h"

using namespace Amboss::KML;
using namespace std;

std::string cmp1_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
    "<Document>\n"
    "  <Placemark>\n"
    "    <Point>\n"
    "      <coordinates>\n"
    "        10,10,0 \n"
    "      </coordinates>\n"
    "    </Point>\n"
    "  </Placemark>\n"
    "</Document>\n"
    "</kml>\n";

std::string cmp2_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
    "<Document>\n"
    "  <Placemark>\n"
    "    <Point>\n"
    "      <coordinates>\n"
    "        10,10,0 \n"
    "      </coordinates>\n"
	    "    </Point>\n"
    "  </Placemark>\n"
    "  <Placemark>\n"
    "    <Point>\n"
    "      <coordinates>\n"
    "        20,20,0 \n"
    "      </coordinates>\n"
    "    </Point>\n"
    "  </Placemark>\n"
    "</Document>\n"
    "</kml>\n";


TEST( KMLWriter , oneTestingPoint )
{
    Writer kmlWriter;
    kmlWriter.add( TestingPoint( 10.0 , 10.0 ) );
    ostringstream str;
    kmlWriter.write( str );
    CPPUNIT_ASSERT( cmp1_ == str.str() );
}

// TEST( KMLWriter , writeFunction )
// {
//     ostringstream str;
//     write( str , TestingPoint( 10.0 , 10.0 ) );
//     CPPUNIT_ASSERT( cmp1_ == str.str() );
// }

// TEST( KMLWriter , writeRangeFunction )
// {
//     ostringstream str;
//     std::vector< Entity > entities;
//     entities.push_back( Entity( TestingPoint( 10.0 , 10.0 ) ) );
//     entities.push_back( Entity( TestingPoint( 20.0 , 20.0 ) ) );
//     writeRange( str , entities );
//     CPPUNIT_ASSERT( cmp2_ == str.str() );
// }


