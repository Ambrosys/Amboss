/*
 * DocumentTest.cpp
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/KML/Document.h>
#include <Amboss/KML/Placemark.h>

#include "TestingPoint.h"

using namespace std;
using namespace Amboss::KML;

TEST( KMLDocument , writeMethod )
{
    Document doc;
    doc.name() = "Document";
    doc.add( Placemark( TestingPoint( 10.0 , 10.0 ) , "Placemark" ) );
    ostringstream str;
    doc.write( str );

    std::string cmp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
        "<Document>\n"
        "  <name>Document</name>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Document>\n"
        "</kml>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLDocument , write )
{
    ostringstream str;
    write( str , Placemark( TestingPoint( 10.0 , 10.0 ) , "Placemark" ) , "Document" );

    std::string cmp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
        "<Document>\n"
        "  <name>Document</name>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Document>\n"
        "</kml>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLDocument , writeRange )
{
    std::vector< Placemark > pm;
    pm.push_back( Placemark( TestingPoint( 10.0 , 10.0 ) , "Placemark" ) );
    pm.push_back( Placemark( TestingPoint( 20.0 , 20.0 ) , "Placemark" ) );
    ostringstream str;
    writeRange( str , pm , "Document" );

    std::string cmp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
        "<Document>\n"
        "  <name>Document</name>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        20,20,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Document>\n"
        "</kml>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLDocument , writePlacemarkRange )
{
    std::vector< TestingPoint > pm;
    pm.push_back( TestingPoint( 10.0 , 10.0 ) );
    pm.push_back( TestingPoint( 20.0 , 20.0 ) );
    ostringstream str;
    writePlacemarkRange( str , pm , "Document" , "Placemark" );

    std::string cmp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
        "<Document>\n"
        "  <name>Document</name>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "  <Placemark>\n"
        "    <name>Placemark</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        20,20,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Document>\n"
        "</kml>\n";

    EXPECT_EQ( cmp , str.str() );
}
