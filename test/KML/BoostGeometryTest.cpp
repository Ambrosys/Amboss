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

#include <gtest/gtest.h>

#include <Amboss/KML/BoostGeometry.h>


using namespace std;
using namespace Amboss::KML;



using namespace std;
using namespace Amboss::KML;

typedef boost::geometry::cs::spherical_equatorial< boost::geometry::degree > CS;
typedef boost::geometry::model::point< double , 2 , CS > Point;
typedef boost::geometry::model::box< Point > Box;
typedef boost::geometry::model::ring< Point > Ring;
typedef boost::geometry::model::segment< Point > Segment;
typedef boost::geometry::model::linestring< Point > LineString;
typedef boost::geometry::model::multi_point< Point > MultiPoint;




TEST( BoostGeometry , testWritePoint )
{
    std::string cmpPoint =
        "<Point>\n"
        "  <coordinates>\n"
        "    10,10,0 \n"
        "  </coordinates>\n"
        "</Point>\n";

    std::ostringstream str;
    writeObject( str , Point( 10.0 , 10.0 ) , 0 );
    EXPECT_EQ( cmpPoint , str.str() );
}


TEST( BoostGeometry , testWriteRing )
{
    std::string cmpRing = 
        "<Polygon>\n"
        "  <tessellate>1</tessellate>\n"
        "  <outerBoundaryIs>\n"
        "    <LinearRing>\n"
        "      <coordinates>\n"
        "        13.34,45.76,0 13.36,45.73,0 13.38,45.74,0 \n"
        "      </coordinates>\n"
        "    </LinearRing>\n"
        "  </outerBoundaryIs>\n"
        "</Polygon>\n";


    Ring r;
    r.push_back( Point( 13.34 , 45.76 ) );
    r.push_back( Point( 13.36 , 45.73 ) );
    r.push_back( Point( 13.38 , 45.74 ) );
    std::ostringstream str;
    writeObject( str , r , 0 );
    EXPECT_EQ( cmpRing , str.str() );
}
    
TEST( BoostGeometry , testWriteBox )
{
    std::string cmpBox = 
        "<Polygon>\n"
        "  <tessellate>1</tessellate>\n"
        "  <outerBoundaryIs>\n"
        "    <LinearRing>\n"
        "      <coordinates>\n"
        "        13.33,45.13,0 13.35,45.13,0 13.35,45.14,0 13.33,45.14,0 13.33,45.13,0 \n"
        "      </coordinates>\n"
        "    </LinearRing>\n"
        "  </outerBoundaryIs>\n"
        "</Polygon>\n";

    std::ostringstream str;
    writeObject( str , Box( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 );
    EXPECT_EQ( cmpBox , str.str() );
}

   
TEST( BoostGeometry , testWriteSegment )
{
    std::string cmpSegment =
        "<LineString>\n"
        "  <tessellate>1</tessellate>\n"
        "  <coordinates>\n"
        "    13.33,45.13, 13.35,45.14, \n"
        "  </coordinates>\n"
        "</LineString>\n";

    std::ostringstream str;
    writeObject( str , Segment( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , 0 );
    EXPECT_EQ( cmpSegment , str.str() );
}
    
TEST( BoostGeometry , testWriteLineString )
{
    std::string cmpLineString_ = 
        "<LineString>\n"
        "  <tessellate>1</tessellate>\n"
        "  <coordinates>\n"
        "    13.34,45.76, 13.36,45.73, 13.38,45.74, \n"
        "  </coordinates>\n"
        "</LineString>\n";

    LineString l;
    l.push_back( Point( 13.34 , 45.76 ) );
    l.push_back( Point( 13.36 , 45.73 ) );
    l.push_back( Point( 13.38 , 45.74 ) );
    std::ostringstream str;
    writeObject( str , l , 0 );
    EXPECT_EQ( cmpLineString_ , str.str() );
}
    
   
TEST( BoostGeometry , testWriteMultiPoint )
{
    std::string cmpMultiPoint = 
        "<Folder>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      13.34,45.76,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      13.36,45.73,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "  <Point>\n"
        "    <coordinates>\n"
        "      13.38,45.74,0 \n"
        "    </coordinates>\n"
        "  </Point>\n"
        "</Folder>\n";

    MultiPoint mp;
    mp.push_back( Point( 13.34 , 45.76 ) );
    mp.push_back( Point( 13.36 , 45.73 ) );
    mp.push_back( Point( 13.38 , 45.74 ) );
    std::ostringstream str;
    writeObject( str , mp , 0 );
    EXPECT_EQ( cmpMultiPoint , str.str() );
}
    
