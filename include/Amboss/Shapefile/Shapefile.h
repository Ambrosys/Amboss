/*
 * Shapefile.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_SHAPEFILE_H_INCLUDED
#define AMBOSS_SHAPEFILE_H_INCLUDED

#include <stdexcept>
#include <memory>

#include <ogrsf_frmts.h>

namespace Amboss {
namespace Shapefile {



struct OGRDSDeleter
{
    void operator()( OGRDataSource *ds ) { OGRDataSource::DestroyDataSource( ds ); }
};



/*
 * Layers is a multi-index container with access by index and access by name
 *
 */
class Shapefile
{
public:

    Shapefile( const std::string &filename = "" )
        : isInit_( false ) , filename_( filename ) , shp_()
    { }

    void setFilename( const std::string &filename )
    {
        filename_ = filename;
        shp_.reset( nullptr );
        isInit_ = false;
    }

    void init( void )
    {
        RegisterOGRShape();

        if( filename_ == "" ) return;

        shp_.reset(  OGRSFDriverRegistrar::Open( filename_.c_str() , FALSE ) );
        if( !shp_ )
            throw std::runtime_error( std::string( "Could not open shapefile " ) + filename_ );

        // GetLayer informations
        // GetFeature informations

        isInit_ = true;
    }

    // auslagern nach Layers
    template< class Visitor >
    void visitAllElements( Visitor visitor )
    {
        if( !isInit_ ) init();

        // OGRLayer *layer = ptr->GetLayerByName( "Bstr_abschnitte" );
        // if( layer == 0 )
        // {
        //     throw std::runtime_error( "No layer Bstr_abschnitte!" );
        // }


        // layer->ResetReading();

        // Road road;
        // OGRFeature *feature;
        // while( ( feature = layer->GetNextFeature() ) != 0 )
        // {
        //     road.id = feature->GetFieldAsInteger( 0 );

        //     OGRGeometry *geometry = feature->GetGeometryRef();
        //     if( ( geometry != 0 ) && ( wkbFlatten( geometry->getGeometryType() ) == wkbLineString ) )
        //     {
        //         OGRLineString *lineString = dynamic_cast< OGRLineString* >( geometry );
        //         if( lineString == 0 )
        //         {
        //             throw std::runtime_error( "lineString == NULL" );
        //         }

        //         road.segment.clear();
        //         for( int i=0 ; i<lineString->getNumPoints() ; ++i )
        //         {
        //             double x = lineString->getX( i );
        //             double y = lineString->getY( i );
        //             road.segment.push_back( GeometryTypes::PointType( { x , y } ) );
        //         }
        //         handler( road );            
        //     }
        //     OGRFeature::DestroyFeature( feature );
        // }

    }

private:

    bool isInit_;
    std::string filename_;
    std::unique_ptr< OGRDataSource , OGRDSDeleter > shp_;

};



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_SHAPEFILE_H_INCLUDED
