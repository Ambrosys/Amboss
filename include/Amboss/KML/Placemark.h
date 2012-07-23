/*
 * Placemark.h
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_KML_PLACEMARK_H_INCLUDED
#define AMBOSS_KML_PLACEMARK_H_INCLUDED

#include <Amboss/KML/Feature.h>
#include <Amboss/KML/Geometry.h>
#include <Amboss/KML/WriterHelper.h>



namespace Amboss {
namespace KML {


class Placemark
{
public:

    Placemark( void ) : geom_() , name_( "" ) { }
    Placemark( const Geometry &geom ) : geom_( geom ) , name_( "" ) { }
    Placemark( const Geometry &geom , const std::string &name ) : geom_( geom ) , name_( name ) { }

    std::string& name( void ) { return name_; }
    const std::string& name( void ) const { return name_; }

    Geometry& geometry( void ) { return geom_; }
    const Geometry& geometry( void ) const { return geom_; }

private:

    Geometry geom_;
    std::string name_;
};

template<>
struct WriteFeature< Placemark >
{
    static inline void write( std::ostream &out , const Placemark &p , size_t indent )
    {
        out << getIndent( indent ) << "<Placemark>" << "\n";
        if( p.name() != "" )
        {
            out << getIndent( indent + 1 ) << "<name>" << p.name() << "</name>" << "\n";
        }
        p.geometry().write( out , indent + 1 );
        out << getIndent( indent ) << "</Placemark>" << "\n";
    }

};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_KML_PLACEMARK_H_INCLUDED
