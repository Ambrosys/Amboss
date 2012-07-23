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
#include <Amboss/KML/ElementWithName.h>
#include <Amboss/KML/ElementWithStyleUrl.h>
#include <Amboss/KML/ElementWithStyle.h>


namespace Amboss {
namespace KML {


class Placemark : public ElementWithName , public ElementWithStyleUrl , public ElementWithStyle
{
public:

    Placemark( void )
        : ElementWithName() , ElementWithStyleUrl() , ElementWithStyle() , geom_()  { }
    Placemark( const Geometry &geom )
        : ElementWithName() , ElementWithStyleUrl() , ElementWithStyle() , geom_( geom ) { }
    Placemark( const Geometry &geom , const std::string &name )
        : ElementWithName( name ) , ElementWithStyleUrl() , ElementWithStyle() , geom_( geom ) { }
    Placemark( const Geometry &geom , const Style &style )
        : ElementWithName() , ElementWithStyleUrl() , ElementWithStyle( style ) , geom_( geom ) { }
    Placemark( const Geometry &geom , const Style &style , const std::string &name )
        : ElementWithName( name ) , ElementWithStyleUrl() , ElementWithStyle( style ) , geom_( geom ) { }

    Geometry& geometry( void ) { return geom_; }
    const Geometry& geometry( void ) const { return geom_; }

private:

    Geometry geom_;
};

template<>
struct WriteFeature< Placemark >
{
    static inline void write( std::ostream &out , const Placemark &p , size_t indent )
    {
        out << getIndent( indent ) << "<Placemark>" << "\n";
        p.writeName( out , indent + 1 );
        p.writeStyleUrl( out , indent + 1 );
        p.writeStyle( out , indent + 1 );
        p.geometry().write( out , indent + 1 );
        out << getIndent( indent ) << "</Placemark>" << "\n";
    }

};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_KML_PLACEMARK_H_INCLUDED
