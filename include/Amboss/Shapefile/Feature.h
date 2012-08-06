/*
 * Feature.h
 * Date: 2012-07-31
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FEATURE_H_INCLUDED
#define AMBOSS_FEATURE_H_INCLUDED

#include <typeinfo>
#include <stdexcept>
#include <memory>

#include <Amboss/Shapefile/FeatureDesc.h>
#include <Amboss/Shapefile/Detail/FieldGetter.h>


namespace Amboss {
namespace Shapefile {



class Feature
{
public:

    Feature( OGRFeature *feature )
        : feature_( feature ) { }


    FeatureDesc featureDesc( void ) const { return makeFeatureDesc( feature_->GetDefnRef() ); }

    template< class OGRGeom >
    const OGRGeom* geometry( void ) const
    {
        const OGRGeom* g = dynamic_cast< const OGRGeom* >( feature_->GetGeometryRef() );
        if( g == 0 )
        {
            std::string error = "Cannot convert geometry to ";
            error += typeid( const OGRGeom* ).name() ;
            throw std::runtime_error( error );
        }
        return g;
    }

    size_t size( void ) const
    {
        return size_t( feature_->GetFieldCount() );
    }
    
    // template< class Geom >
    // Geom geometry( void ) const { };

    template< class T >
    T get( size_t id ) const
    {
        if( int( id ) >= feature_->GetFieldCount() )
        {
            std::string error = std::string( "Index " ) + std::to_string( id );
            error += " is larger then number of fields " + std::to_string( feature_->GetFieldCount() ) ;
            throw std::runtime_error( error );
        }
        return Detail::FieldGetter< T >::getValue( int( id ) , feature_ );
    }

    template< class T >
    T get( const std::string &fieldName ) const
    {
        int id = feature_->GetFieldIndex( fieldName.c_str() );
        if( id < 0 )
        {
            std::string error = std::string( "Cannot find feature field for key " ) + fieldName;
            throw std::runtime_error( error );
        }
        return Detail::FieldGetter< T >::getValue( id , feature_ );
    }

private:

    struct OGRFeatureDeleter
    {
        void operator()( OGRFeature *f ) const
        {
            OGRFeature::DestroyFeature( f );
        }
    };

     std::unique_ptr< OGRFeature , OGRFeatureDeleter >  feature_;
};

inline Feature makeFeature( OGRFeature *f )
{
    return Feature( f );
}



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_FEATURE_H_INCLUDED
