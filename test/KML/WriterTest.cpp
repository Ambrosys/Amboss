/*
 * WriterTest.cpp
 *
 *  Created on: 19.06.2012
 *      Author: karsten
 */

#include <sstream>
#include <iostream>

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Amboss/KML/WriterHelper.h>
#include <Amboss/KML/Writer.h>

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
struct WriteObject< TestingPoint >
{
    static void write( std::ostream &out , const TestingPoint &p , size_t indent , const std::string &name )
    {
	writePoint( out , p.x , p.y , indent , name );
    }
};

} // namespace KML
} // namespace Amboss

using namespace std;

class TEST_NAME : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TEST_NAME );
    CPPUNIT_TEST( testOneTestingPoint );
    CPPUNIT_TEST( testWriteFunction );
    CPPUNIT_TEST( testWriteRangeFunction );
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp()
    {
        cmp1_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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

        cmp2_ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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

    }

    void tearDown()
    {
    }


protected:

    std::string cmp1_;
    std::string cmp2_;

    void testOneTestingPoint( void )
    {
	Writer kmlWriter;
	kmlWriter.add( TestingPoint( 10.0 , 10.0 ) );
	ostringstream str;
	kmlWriter.write( str );
	CPPUNIT_ASSERT( cmp1_ == str.str() );
    }

    void testWriteFunction( void )
    {
	ostringstream str;
        write( str , TestingPoint( 10.0 , 10.0 ) );
	CPPUNIT_ASSERT( cmp1_ == str.str() );
    }

    void testWriteRangeFunction( void )
    {
	ostringstream str;
        std::vector< Entity > entities;
        entities.push_back( Entity( TestingPoint( 10.0 , 10.0 ) ) );
        entities.push_back( Entity( TestingPoint( 20.0 , 20.0 ) ) );
        writeRange( str , entities );
	CPPUNIT_ASSERT( cmp2_ == str.str() );
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );
