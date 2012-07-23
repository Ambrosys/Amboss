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
    Layer water = shp.layersByName().find( "line" )->second;
}
