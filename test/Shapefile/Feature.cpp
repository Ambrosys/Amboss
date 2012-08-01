/*
 * Feature.cpp
 * Date: 2012-08-01
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>
#include <memory>

#include <gtest/gtest.h>

#include <Amboss/Shapefile/Feature.h>

using namespace std;
using namespace Amboss::Shapefile;


class ShapefileFeature : public ::testing::Test
{
protected:

    struct OGRFeatureDeleter
    {
        void operator()( OGRFeature *f ) const
        {
            OGRFeature::DestroyFeature( f ) ;
        }
    };


    virtual void SetUp( void )
    {
        defn_.reset( new OGRFeatureDefn( "TestDefn" ) );
    }

    virtual void TearDown( void )
    {
        feature_.reset( 0 );
        defn_.reset( 0 );
    }

    std::unique_ptr< OGRFeature , OGRFeatureDeleter > feature_;
    std::unique_ptr< OGRFeatureDefn > defn_;

};



TEST_F( ShapefileFeature , testConstruction )
{
    EXPECT_EQ( true , true );
}
