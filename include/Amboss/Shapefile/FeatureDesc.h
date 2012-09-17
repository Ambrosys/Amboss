/*
 * FeatureDesc.h
 * Date: 2012-07-31
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FEATUREDESC_INCLUDED
#define AMBOSS_FEATUREDESC_INCLUDED

#include <string>
#include <utility>
#include <exception>

#include <ogrsf_frmts.h>

#include <Amboss/Shapefile/FieldDesc.h>


namespace Amboss {
namespace Shapefile {



class FeatureDesc
{

public:

    /*
     * Possible values :
     * wkbUnknown , wkbPoint , wkbLineString , wkbPolygon , wkbMultiPoint , wkbMultiLineString ,
     * wkbMultiPolygon ,wkbGeometryCollection , wkbNone , wkbLinearRing , wkbPoint25D ,
     * wkbLineString25D , wkbPolygon25D , wkbMultiPoint25D , wkbMultiLineString25D ,
     * wkbMultiPolygon25D , wkbGeometryCollection25D
     */
    typedef OGRwkbGeometryType GeometryType;
    typedef std::vector< FieldDesc > FieldContainer;


    FeatureDesc( OGRFeatureDefn * defn )
        : defn_( defn ) , fields_()
    {
        try
        {
            init();
        }
        catch( std::exception &e )
        {
            std::rethrow_exception( std::make_exception_ptr( e ) );
        }
    }

    std::string name( void ) const { return defn_->GetName(); }

    GeometryType geometryType( void ) const { return defn_->GetGeomType(); }
    std::string geometryTypeName( void ) const { return std::string( OGRGeometryTypeToName( geometryType() ) ); }


    const FieldContainer& fields( void ) const { return fields_; }


private:

    void init( void )
    {
        for( int i=0 ; i<defn_->GetFieldCount() ; ++i )
        {
            OGRFieldDefn *field = defn_->GetFieldDefn( i );
            fields_.push_back(  makeFieldDesc( field ) );
        }
    }

    OGRFeatureDefn * defn_;
    FieldContainer fields_;
};


inline FeatureDesc makeFeatureDesc( OGRFeatureDefn * defn )
{
    return FeatureDesc( defn );
}



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_FEATUREDESC_INCLUDED
