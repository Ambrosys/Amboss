/*
 * EntityTest.cpp
 *
 *  Created on: 19.06.2012
 *      Author: karsten
 */

#include <sstream>
#include <iostream>

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Amboss/KML/Entity.h>
#include <Amboss/KML/BoostGeometry.h>

#define TEST_NAME KMLBoostGeometryTest

using namespace Amboss::KML;



using namespace std;

class TEST_NAME : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TEST_NAME );
    CPPUNIT_TEST( testWritePoint );
    CPPUNIT_TEST( testWritePointName );
    CPPUNIT_TEST( testWriteRing );
    CPPUNIT_TEST( testWriteRingName );
    CPPUNIT_TEST( testWriteBox );
    CPPUNIT_TEST( testWriteBoxName );
    CPPUNIT_TEST( testWriteSegment );
    CPPUNIT_TEST( testWriteSegmentName );
    CPPUNIT_TEST( testWriteLineString );
    CPPUNIT_TEST( testWriteLineStringName );
    CPPUNIT_TEST( testWriteMultiPoint );
    CPPUNIT_TEST( testWriteMultiPointName );
    CPPUNIT_TEST_SUITE_END();

    std::string cmpPoint_ , cmpPointName_;
    std::string cmpRing_ , cmpRingName_;
    std::string cmpBox_ , cmpBoxName_;
    std::string cmpSegment_ , cmpSegmentName_;
    std::string cmpLineString_ , cmpLineStringName_;
    std::string cmpMultiPoint_ , cmpMultiPointName_;

public:

    void setUp()
    {
        cmpPoint_ ="<Placemark>\n"
	    "  <Point>\n"
	    "    <coordinates>\n"
	    "      10,10,0 \n"
	    "    </coordinates>\n"
	    "  </Point>\n"
	    "</Placemark>\n";
        cmpPointName_ ="<Placemark>\n"
            "  <name>Point</name>\n"
	    "  <Point>\n"
	    "    <coordinates>\n"
	    "      10,10,0 \n"
	    "    </coordinates>\n"
	    "  </Point>\n"
	    "</Placemark>\n";
        cmpRing_ = "<Placemark>\n"
            "  <Polygon>\n"
            "    <tessellate>1</tessellate>\n"
            "    <outerBoundaryIs>\n"
            "      <LinearRing>\n"
            "        <coordinates>\n"
            "          13.34,45.76,0 13.36,45.73,0 13.38,45.74,0 \n"
            "        </coordinates>\n"
            "      </LinearRing>\n"
            "    </outerBoundaryIs>\n"
            "  </Polygon>\n"
            "</Placemark>\n";
        cmpRingName_ = "<Placemark>\n"
            "  <name>Ring</name>\n"
            "  <Polygon>\n"
            "    <tessellate>1</tessellate>\n"
            "    <outerBoundaryIs>\n"
            "      <LinearRing>\n"
            "        <coordinates>\n"
            "          13.34,45.76,0 13.36,45.73,0 13.38,45.74,0 \n"
            "        </coordinates>\n"
            "      </LinearRing>\n"
            "    </outerBoundaryIs>\n"
            "  </Polygon>\n"
            "</Placemark>\n";
        cmpBox_ = "<Placemark>\n"
            "  <Polygon>\n"
            "    <tessellate>1</tessellate>\n"
            "    <outerBoundaryIs>\n"
            "      <LinearRing>\n"
            "        <coordinates>\n"
            "          13.33,45.13,0 13.35,45.13,0 13.35,45.14,0 13.33,45.14,0 13.33,45.13,0 \n"
            "        </coordinates>\n"
            "      </LinearRing>\n"
            "    </outerBoundaryIs>\n"
            "  </Polygon>\n"
            "</Placemark>\n";
        cmpBoxName_ = "<Placemark>\n"
            "  <name>Box</name>\n"
            "  <Polygon>\n"
            "    <tessellate>1</tessellate>\n"
            "    <outerBoundaryIs>\n"
            "      <LinearRing>\n"
            "        <coordinates>\n"
            "          13.33,45.13,0 13.35,45.13,0 13.35,45.14,0 13.33,45.14,0 13.33,45.13,0 \n"
            "        </coordinates>\n"
            "      </LinearRing>\n"
            "    </outerBoundaryIs>\n"
            "  </Polygon>\n"
            "</Placemark>\n";
        cmpSegment_ = "<Placemark>\n"
            "  <LineString>\n"
            "    <tessellate>1</tessellate>\n"
            "    <coordinates>\n"
            "      13.33,45.13, 13.35,45.14, \n"
            "    </coordinates>\n"
            "  </LineString>\n"
            "</Placemark>\n";
        cmpSegmentName_ = "<Placemark>\n"
            "  <name>Segment</name>\n"
            "  <LineString>\n"
            "    <tessellate>1</tessellate>\n"
            "    <coordinates>\n"
            "      13.33,45.13, 13.35,45.14, \n"
            "    </coordinates>\n"
            "  </LineString>\n"
            "</Placemark>\n";
        cmpLineString_ = "<Placemark>\n"
            "  <LineString>\n"
            "    <tessellate>1</tessellate>\n"
            "    <coordinates>\n"
            "      13.34,45.76, 13.36,45.73, 13.38,45.74, \n"
            "    </coordinates>\n"
            "  </LineString>\n"
            "</Placemark>\n";
        cmpLineStringName_ = "<Placemark>\n"
            "  <name>LineString</name>\n"
            "  <LineString>\n"
            "    <tessellate>1</tessellate>\n"
            "    <coordinates>\n"
            "      13.34,45.76, 13.36,45.73, 13.38,45.74, \n"
            "    </coordinates>\n"
            "  </LineString>\n"
            "</Placemark>\n";
        cmpMultiPoint_ = "<Folder>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.34,45.76,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.36,45.73,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.38,45.74,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "</Folder>\n";
        cmpMultiPointName_ = "<Folder>\n"
            "  <name>MultiPoint</name>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.34,45.76,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.36,45.73,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "  <Placemark>\n"
            "    <Point>\n"
            "      <coordinates>\n"
            "        13.38,45.74,0 \n"
            "      </coordinates>\n"
            "    </Point>\n"
            "  </Placemark>\n"
            "</Folder>\n";


    }

    void tearDown()
    {
    }

protected:

    typedef boost::geometry::cs::spherical_equatorial< boost::geometry::degree > CS;
    typedef boost::geometry::model::point< double , 2 , CS > Point;
    typedef boost::geometry::model::box< Point > Box;
    typedef boost::geometry::model::ring< Point > Ring;
    typedef boost::geometry::model::segment< Point > Segment;
    typedef boost::geometry::model::linestring< Point > LineString;
    typedef boost::geometry::model::multi_point< Point > MultiPoint;


    void testWritePoint( void )
    {
        std::ostringstream str;
        writeObject( str , Point( 10.0 , 10.0 ) , 0 , "" );
        CPPUNIT_ASSERT( cmpPoint_ == str.str() );
    }

    void testWritePointName( void )
    {
        std::ostringstream str;
        writeObject( str , Point( 10.0 , 10.0 ) , 0 , "Point" );
        CPPUNIT_ASSERT( cmpPointName_ == str.str() );
    }

    void testWriteRing( )
    {
        Ring r;
        r.push_back( Point( 13.34 , 45.76 ) );
        r.push_back( Point( 13.36 , 45.73 ) );
        r.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , r , 0 , "" );
        CPPUNIT_ASSERT( cmpRing_ == str.str() );

    }
    void testWriteRingName( )
    {
        Ring r;
        r.push_back( Point( 13.34 , 45.76 ) );
        r.push_back( Point( 13.36 , 45.73 ) );
        r.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , r , 0 , "Ring" );
        CPPUNIT_ASSERT( cmpRingName_ == str.str() );
    }
    
    void testWriteBox( )
    {
        std::ostringstream str;
        writeObject( str , Box( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 , "" );
        CPPUNIT_ASSERT( cmpBox_ == str.str() );
    }

    void testWriteBoxName( )
    {
        std::ostringstream str;
        writeObject( str , Box( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 , "Box" );
        CPPUNIT_ASSERT( cmpBoxName_ == str.str() );
    }
    
    void testWriteSegment( )
    {
        std::ostringstream str;
        writeObject( str , Segment( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 , "" );
        CPPUNIT_ASSERT( cmpSegment_ == str.str() );
    }
    
    void testWriteSegmentName( )
    {
        std::ostringstream str;
        writeObject( str , Segment( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 , "Segment" );
        CPPUNIT_ASSERT( cmpSegmentName_ == str.str() );
    }
    
    void testWriteLineString( )
    {
        LineString l;
        l.push_back( Point( 13.34 , 45.76 ) );
        l.push_back( Point( 13.36 , 45.73 ) );
        l.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , l , 0 , "" );
        CPPUNIT_ASSERT( cmpLineString_ == str.str() );
    }
    
    void testWriteLineStringName( )
    {
        LineString l;
        l.push_back( Point( 13.34 , 45.76 ) );
        l.push_back( Point( 13.36 , 45.73 ) );
        l.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , l , 0 , "LineString" );
        CPPUNIT_ASSERT( cmpLineStringName_ == str.str() );
    }
    
    void testWriteMultiPoint( )
    {
        MultiPoint mp;
        mp.push_back( Point( 13.34 , 45.76 ) );
        mp.push_back( Point( 13.36 , 45.73 ) );
        mp.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , mp , 0 , "" );
        CPPUNIT_ASSERT( cmpMultiPoint_ == str.str() );
    }
    
    void testWriteMultiPointName( )
    {
        MultiPoint mp;
        mp.push_back( Point( 13.34 , 45.76 ) );
        mp.push_back( Point( 13.36 , 45.73 ) );
        mp.push_back( Point( 13.38 , 45.74 ) );
        std::ostringstream str;
        writeObject( str , mp , 0 , "MultiPoint" );
        CPPUNIT_ASSERT( cmpMultiPointName_ == str.str() );
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );
