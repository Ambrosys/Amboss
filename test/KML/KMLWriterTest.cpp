/*
 * KMLWriterTest.cpp
 *
 *  Created on: 19.06.2012
 *      Author: karsten
 */

#include <sstream>
#include <iostream>

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Amboss/KML/KMLWriterHelper.h>
#include <Amboss/KML/KMLWriter.h>

#define TEST_NAME KMLWriterTest

using namespace Amboss::KML;

struct TestingPoint
{
    TestingPoint( void ) : x( 0.0 ) , y( 0.0 ) { }
    TestingPoint( double _x , double _y ) : x( _x ) , y( _y ) { }
    double x;
    double y;
};

namespace Amboss {
namespace KML {

template<>
struct WriteKMLObject< TestingPoint >
{
    static void write( std::ostream &out , const TestingPoint &p , size_t indent , const std::string &name )
    {
	writeKMLPoint( out , p.x , p.y , indent , name );
    }
};

} // namespace KML
} // namespace Amboss

using namespace std;

class TEST_NAME : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TEST_NAME );
    CPPUNIT_TEST( testOneTestingPoint );
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp()
    {
    }

    void tearDown()
    {
    }

protected:

    void testOneTestingPoint( void )
    {
	KMLWriter kmlWriter;
	kmlWriter.add( TestingPoint( 10.0 , 10.0 ) );
	ostringstream str;
	kmlWriter.write( str );

	string cmp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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

	CPPUNIT_ASSERT( cmp == str.str() );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );
