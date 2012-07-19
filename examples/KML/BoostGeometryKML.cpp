/*
 * BoostGeometryKML.cpp
 * Date: 2012-07-03
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>

#include <Amboss/KML.h>

using namespace std;
using namespace Amboss::KML;

typedef boost::geometry::cs::spherical_equatorial< boost::geometry::degree > CS;
typedef boost::geometry::model::point< double , 2 , CS > Point;
typedef boost::geometry::model::box< Point > Box;
typedef boost::geometry::model::ring< Point > Ring;
typedef boost::geometry::model::segment< Point > Segment;
typedef boost::geometry::model::linestring< Point > LineString;
typedef boost::geometry::model::multi_point< Point > MultiPoint;

int main( int argc , char **argv )
{
    Folder folder;
    folder.add( Placemark( Point( 13.33 , 45.12 ) , "Point" ) );
    folder.add( Placemark( Box( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , "Box" ) );
    folder.add( Placemark( Segment( Point( 13.33 , 45.13 ) , Point( 13.35 , 45.14 ) ) , "Segment" ) );

    Ring r;
    r.push_back( Point( 13.34 , 45.76 ) );
    r.push_back( Point( 13.36 , 45.73 ) );
    r.push_back( Point( 13.38 , 45.74 ) );
    folder.add( Placemark( r , "Ring" ) );

    LineString l;
    l.push_back( Point( 13.34 , 45.76 ) );
    l.push_back( Point( 13.36 , 45.73 ) );
    l.push_back( Point( 13.38 , 45.74 ) );
    folder.add( Placemark( l , "LineString" ) );

    // MultiPoint mp;
    // mp.push_back( Point( 13.34 , 45.76 ) );
    // mp.push_back( Point( 13.36 , 45.73 ) );
    // mp.push_back( Point( 13.38 , 45.74 ) );
    // folder.add( mp , "MultiPoint" );

    write( cout , folder , "Testing" );
    
    return 0;
}
