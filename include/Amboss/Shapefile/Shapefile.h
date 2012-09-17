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

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/utility.hpp>

#include <ogrsf_frmts.h>

#include <Amboss/Shapefile/Layer.h>
#include <Amboss/Shapefile/MITags.h>

namespace Amboss {
namespace Shapefile {


class Shapefile : boost::noncopyable
{
public:

    typedef std::pair< std::string , Layer > LayerContainerElement;
    typedef mi::random_access< mi::tag< ById , ByIndex > > RandomAccessIndex ;
    typedef mi::ordered_unique< mi::tag< ByName > ,
                                mi::member< LayerContainerElement , std::string , &LayerContainerElement::first > > HashIndex;
    typedef mi::multi_index_container<
        LayerContainerElement ,
        mi::indexed_by< RandomAccessIndex , HashIndex >
        > LayerContainer;

    typedef typename LayerContainer::index< ByName >::type LayerContainerByName;
    typedef typename LayerContainer::index< ByIndex >::type LayerContainerByIndex;

    Shapefile( void )
        : filename_() , shp_() , layers_()
    {
    }


    Shapefile( const std::string &filename = "" )
        : filename_() , shp_() , layers_()
    {
        open( filename );
    }

    void open( const std::string &filename )
    {
        RegisterOGRShape();
        
        if( filename == "" ) return;

        shp_.reset( OGRSFDriverRegistrar::Open( filename.c_str() , FALSE ) );
        if( !shp_ )
        {
            throw std::runtime_error( std::string( "Could not open shapefile " ) + filename_ );
        }
        buildLayers();

        filename_ = filename;
    }


    std::string name( void ) const { return std::string( shp_->GetName() ); }

    LayerContainer& layers( void ) { return layers_; }
    LayerContainerByName& layersByName( void ) { return layers_.get< ByName >(); }
    LayerContainerByIndex& layersByIndex( void ) { return layers_.get< ByIndex >(); }
    OGRDataSource* ogrDataSource( void ) { return shp_.get(); }

private:

    void buildLayers( void )
    {
        for( int i=0 ; i<shp_->GetLayerCount() ; ++i )
        {
            OGRLayer *layer = shp_->GetLayer( i );
            if( !layer )
            {
                throw std::runtime_error( std::string( "Cannot create Layer " ) + std::to_string( i ) + " in shapefile " + filename_ );
            }
            layers_.push_back( std::make_pair( std::string( layer->GetName() ) , makeLayer( layer ) ) );
        }
    }

    struct OGRDSDeleter
    {
        void operator()( OGRDataSource *ds ) { OGRDataSource::DestroyDataSource( ds ); }
    };

    bool isInit_;
    std::string filename_;
    std::unique_ptr< OGRDataSource , OGRDSDeleter > shp_;
    LayerContainer layers_;
};



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_SHAPEFILE_H_INCLUDED
