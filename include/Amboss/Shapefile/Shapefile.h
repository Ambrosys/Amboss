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


    Shapefile( const std::string &filename = "" )
        : isInit_( false ) , filename_( filename ) , shp_() , layers_()
    {
        try
        {
            init();
        }
        catch( std::exception &e )
        {
            std::cerr << "Can not initialize shapefile from " << filename_ << ", Error : " << e.what() << "\n";
        }
    }

    std::string name( void ) const { return std::string( shp_->GetName() ); }

    const LayerContainer& layers( void ) const { return layers_; }
    const LayerContainerByName& layersByName( void ) const { layers_.get< ByName >(); }
    const LayerContainerByIndex& layersByIndex( void ) const { layers_.get< ByIndex >(); }
    
    // LayerContainer& layers( void ) { return layers_; }

private:

    void init( void )
    {
        RegisterOGRShape();

        if( filename_ == "" ) return;

        shp_.reset( OGRSFDriverRegistrar::Open( filename_.c_str() , FALSE ) );
        if( !shp_ )
        {
            throw std::runtime_error( std::string( "Could not open shapefile " ) + filename_ );
        }

        buildLayers();

        isInit_ = true;
    }

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
