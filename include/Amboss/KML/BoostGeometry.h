/*
 * KMLEntityAdapters.h
 * Date: 2012-07-03
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_KML_BOOSTGEOMETRY_H_INCLUDED
#define AMBOSS_KML_BOOSTGEOMETRY_H_INCLUDED

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>

#include <Amboss/KML/Writeable.h>
#include <Amboss/KML/Folder.h>
#include <Amboss/KML/WriterHelper.h>


namespace Amboss {
namespace KML {

    template< typename Value >
    struct WriteObject<
        boost::geometry::model::point< Value , 2 ,
                                       boost::geometry::cs::spherical_equatorial< boost::geometry::degree > > >
    {
        typedef boost::geometry::model::point< Value , 2 ,
                                               boost::geometry::cs::spherical_equatorial< boost::geometry::degree > > Point;

        static void write( std::ostream &out , const Point &p , size_t indent )
        {
            namespace bg = boost::geometry;
            writePoint( out , bg::get< 0 >( p ) , bg::get< 1 >( p ) , indent );
        }
    };


    template< typename Point >
    struct WriteObject< boost::geometry::model::ring< Point >  >
    {
        typedef boost::geometry::model::ring< Point > Ring;
        static void write( std::ostream &out , const Ring &r , size_t indent )
        {
            namespace bg = boost::geometry;
            out << getIndent( indent + 0 ) << "<Polygon>" << "\n";
            out << getIndent( indent + 1 ) << "<tessellate>1</tessellate>" << "\n";
            out << getIndent( indent + 1 ) << "<outerBoundaryIs>" << "\n";
            out << getIndent( indent + 2 ) << "<LinearRing>" << "\n";
            out << getIndent( indent + 3 ) << "<coordinates>" << "\n";
            out << getIndent( indent + 4 );
            for( size_t i=0 ; i<r.size() ; ++i )
                out << bg::get< 0 >( r[i] ) << "," << bg::get< 1 >( r[i] ) << ",0 ";
            out << "\n";
            out << getIndent( indent + 3 ) << "</coordinates>" << "\n";
            out << getIndent( indent + 2 ) << "</LinearRing>" << "\n";
            out << getIndent( indent + 1 ) << "</outerBoundaryIs>" << "\n";
            out << getIndent( indent + 0 ) << "</Polygon>" << "\n";
        }
    };

    template< typename Point >
    struct WriteObject< boost::geometry::model::box< Point >  >
    {
        typedef boost::geometry::model::box< Point > Box;
        static void write( std::ostream &out , const Box &b , size_t indent )
        {
            namespace bg = boost::geometry;
            typedef typename bg::coordinate_type< Box >::type ValueType;
            ValueType x1 = bg::get< 0 >( b.min_corner() );
            ValueType x2 = bg::get< 0 >( b.max_corner() );
            ValueType y1 = bg::get< 1 >( b.min_corner() );
            ValueType y2 = bg::get< 1 >( b.max_corner() );

            out << getIndent( indent     ) << "<Polygon>" << "\n";
            out << getIndent( indent + 1 ) << "<tessellate>1</tessellate>" << "\n";
            out << getIndent( indent + 1 ) << "<outerBoundaryIs>" << "\n";
            out << getIndent( indent + 2 ) << "<LinearRing>" << "\n";
            out << getIndent( indent + 3 ) << "<coordinates>" << "\n";
            out << getIndent( indent + 4 ) << x1 << "," << y1 << ",0 ";
            out << x2 << "," << y1 << ",0 ";
            out << x2 << "," << y2 << ",0 ";
            out << x1 << "," << y2 << ",0 ";
            out << x1 << "," << y1 << ",0 " << "\n";
            out << getIndent( indent + 3 ) << "</coordinates>" << "\n";
            out << getIndent( indent + 2 ) << "</LinearRing>" << "\n";
            out << getIndent( indent + 1 ) << "</outerBoundaryIs>" << "\n";
            out << getIndent( indent     ) << "</Polygon>" << "\n";
        }
    };

    template< typename Point >
    struct WriteObject< boost::geometry::model::segment< Point >  >
    {
        typedef boost::geometry::model::segment< Point > Segment;
        static void write( std::ostream &out , const Segment &s , size_t indent )
        {
            namespace bg = boost::geometry;
            out << getIndent( indent + 0 ) << "<LineString>" << "\n";
            out << getIndent( indent + 1 ) << "<tessellate>1</tessellate>" << "\n";
            out << getIndent( indent + 1 ) << "<coordinates>" << "\n";
            out << getIndent( indent + 2 ) << bg::get< 0 >( s.first ) << "," << bg::get< 1 >( s.first ) << ", ";
            out << bg::get< 0 >( s.second ) << "," << bg::get< 1 >( s.second ) << ", ";
            out << "\n";
            out << getIndent( indent + 1 ) << "</coordinates>" << "\n";
            out << getIndent( indent + 0 ) << "</LineString>" << "\n";
        }
    };

    template< typename Point >
    struct WriteObject< boost::geometry::model::linestring< Point >  >
    {
        typedef boost::geometry::model::linestring< Point > LineString;
        static void write( std::ostream &out , const LineString &l , size_t indent )
        {
            namespace bg = boost::geometry;
            out << getIndent( indent + 0 ) << "<LineString>" << "\n";
            out << getIndent( indent + 1 ) << "<tessellate>1</tessellate>" << "\n";
            out << getIndent( indent + 1 ) << "<coordinates>" << "\n";
            out << getIndent( indent + 2 );
            for( size_t i=0 ; i<l.size() ; ++i )
                out << bg::get< 0 >( l[i] ) << "," << bg::get< 1 >( l[i] ) << ", ";
            out << "\n";
            out << getIndent( indent + 1 ) << "</coordinates>" << "\n";
            out << getIndent( indent + 0 ) << "</LineString>" << "\n";
        }
    };

    // template< typename Point >
    // struct WriteObject< boost::geometry::model::multi_point< Point >  >
    // {
    //     typedef boost::geometry::model::multi_point< Point > MultiPoint;
    //     static void write( std::ostream &out , const MultiPoint &mp , size_t indent , const std::string &name )
    //     {
    //         Folder folder;
    //         for( size_t i=0 ; i<mp.size() ; ++i )
    //             folder.add( mp[i] );
    //         writeObject( out , folder , indent , name );
    //     }
    // };




} // KML
} // SuperToll

#endif // AMBOSS_KML_BOOSTGEOMETRY_H_INCLUDED
