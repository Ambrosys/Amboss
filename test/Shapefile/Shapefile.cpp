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
            EXPECT_THROW( { const OGRPoint* p = f.geometry< OGRPoint >(); } , std::runtime_error );
        } );

    vector< pair< string , string > > featureFields;
    featureFields.push_back( pair< string , string >( "First" , "Line" ) );
    featureFields.push_back( pair< string , string >( "Appended" , "Line" ) );
    count = 0;
    lineLayer.visitFeatures( [&count,&featureFields] ( const Feature &f ) {
            EXPECT_EQ( f.size() , 2 );
            EXPECT_EQ( featureFields[count].first , f.get< string >( 0 ) );
            EXPECT_EQ( featureFields[count].second , f.get< string >( 1 ) );
            EXPECT_THROW( { std::string tmp = f.get< string >( 2 ); } , std::runtime_error );
            ++count; } );


    vector< vector< tuple< double , double , double > > > points;
    vector< tuple< double , double , double > > points1 , points2;
    points1.push_back( make_tuple( 1.0 , 5.0 , 0.0 ) );
    points1.push_back( make_tuple( 5.0 , 5.0 , 0.0 ) );
    points1.push_back( make_tuple( 5.0 , 1.0 , 0.0 ) );
    points1.push_back( make_tuple( 3.0 , 3.0 , 0.0 ) );
    points1.push_back( make_tuple( 1.0 , 1.0 , 0.0 ) );
    points2.push_back( make_tuple( 10.0 , 5.0 , 0.0 ) );
    points2.push_back( make_tuple( 15.0 , 5.0 , 0.0 ) );
    points2.push_back( make_tuple( 15.0 , 1.0 , 0.0 ) );
    points2.push_back( make_tuple( 13.0 , 3.0 , 0.0 ) );
    points2.push_back( make_tuple( 11.0 , 1.0 , 0.0 ) );
    points.push_back( points1 );
    points.push_back( points2 );
    count = 0;
    lineLayer.visitFeatures( [&count,&points] ( const Feature &f ) {
            const OGRLineString* l = f.geometry< OGRLineString >();
            EXPECT_EQ( l->getDimension() , 1 );
            EXPECT_EQ( l->getNumPoints() , 5 );
            EXPECT_DOUBLE_EQ( get< 0 >( points[count][0] ) , l->getX( 0 ) );
            EXPECT_DOUBLE_EQ( get< 0 >( points[count][1] ) , l->getX( 1 ) );
            EXPECT_DOUBLE_EQ( get< 0 >( points[count][2] ) , l->getX( 2 ) );
            EXPECT_DOUBLE_EQ( get< 0 >( points[count][3] ) , l->getX( 3 ) );
            EXPECT_DOUBLE_EQ( get< 0 >( points[count][4] ) , l->getX( 4 ) );

            EXPECT_DOUBLE_EQ( get< 1 >( points[count][0] ) , l->getY( 0 ) );
            EXPECT_DOUBLE_EQ( get< 1 >( points[count][1] ) , l->getY( 1 ) );
            EXPECT_DOUBLE_EQ( get< 1 >( points[count][2] ) , l->getY( 2 ) );
            EXPECT_DOUBLE_EQ( get< 1 >( points[count][3] ) , l->getY( 3 ) );
            EXPECT_DOUBLE_EQ( get< 1 >( points[count][4] ) , l->getY( 4 ) );

            EXPECT_DOUBLE_EQ( get< 2 >( points[count][0] ) , l->getZ( 0 ) );
            EXPECT_DOUBLE_EQ( get< 2 >( points[count][1] ) , l->getZ( 1 ) );
            EXPECT_DOUBLE_EQ( get< 2 >( points[count][2] ) , l->getZ( 2 ) );
            EXPECT_DOUBLE_EQ( get< 2 >( points[count][3] ) , l->getZ( 3 ) );
            EXPECT_DOUBLE_EQ( get< 2 >( points[count][4] ) , l->getZ( 4 ) );

            ++count;
        } );

}
