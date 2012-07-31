/*
 * Shapefile.cpp
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/Shapefile/Shapefile.h>

using namespace std;
using namespace Amboss::Shapefile;

TEST( ShapefileShapefile , testConstruction )
{
    Shapefile shp( "samples" );
    EXPECT_EQ( shp.name() , "samples" );
    EXPECT_EQ( shp.layers().size() , 4 );
    EXPECT_EQ( shp.layersByName().count( "blockgroups" ) , 1 );
    EXPECT_EQ( shp.layersByName().count( "line" ) , 1 );
    EXPECT_EQ( shp.layersByName().count( "point" ) , 1 );
    EXPECT_EQ( shp.layersByName().count( "polygon" ) , 1 );
}

TEST( ShapefileShapefile , testLineLayer )
{
    Shapefile shp( "samples" );
    Layer lineLayer = shp.layersByName().find( "line" )->second;
    
    EXPECT_EQ( lineLayer.geometryType() , wkbLineString );

    FeatureDesc fDesc = lineLayer.featureDesc();
    FeatureDesc::FieldContainer fields = fDesc.fields();
    EXPECT_EQ( fields.size() , 2 );
    EXPECT_EQ( fields[0].name() , "FIRST_FLD" );
    EXPECT_EQ( fields[1].name() , "SECOND_FLD" );
    EXPECT_EQ( fields[0].typeName() , "String" );
    EXPECT_EQ( fields[1].typeName() , "String" );

    size_t count = 0;
    lineLayer.visitFeatures( [&count] ( const Feature &f ) {
            ++count; } );
    EXPECT_EQ( count , 2 );

    lineLayer.visitFeatures( [] ( const Feature &f ) {
            EXPECT_NO_THROW( { const OGRLineString* l = f.geometry< OGRLineString >(); } );
            ASSERT_THROW( { const OGRPoint* p = f.geometry< OGRPoint >(); } , std::runtime_error );
        } );

    lineLayer.visitFeatures( [] ( const Feature &f ) {
            cout << f.get< std::string >( 0 ) << "\t" << f.get< std::string >( 1 ) << "\n"; } );


}
