/*
 * Layer.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LAYER_H_INCLUDED
#define AMBOSS_LAYER_H_INCLUDED

#include <ogrsf_frmts.h>

#include <Amboss/Shapefile/FeatureDesc.h>
#include <Amboss/Shapefile/Feature.h>


namespace Amboss {
namespace Shapefile {



class Layer
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

    Layer( OGRLayer *ogrLayer ) : ogrLayer_( ogrLayer ) { }

    std::string name( void ) const { return ogrLayer_->GetName(); }
    
    GeometryType geometryType( void ) const { return ogrLayer_->GetGeomType(); }
    std::string geometryTypeName( void ) const { return std::string( OGRGeometryTypeToName( geometryType() ) ); }

    FeatureDesc featureDesc( void ) const { return makeFeatureDesc( ogrLayer_->GetLayerDefn() ); }

    template< class Handler >
    void visitFeatures( Handler h )
    {
        ogrLayer_->ResetReading();
        OGRFeature *feature = ogrLayer_->GetNextFeature();
        while( feature != 0 )
        {
            h( makeFeature( feature ) );
            OGRFeature::DestroyFeature( feature );
            feature = ogrLayer_->GetNextFeature();
        }
    }

    // visitFeatures mit Filters

private:

    OGRLayer *ogrLayer_;
};

Layer makeLayer( OGRLayer *ogrLayer )
{
    return Layer( ogrLayer );
}



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_LAYER_H_INCLUDED
