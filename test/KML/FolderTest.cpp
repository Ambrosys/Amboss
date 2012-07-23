/*
 * FolderTest.cpp
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/KML/Folder.h>
#include <Amboss/KML/Placemark.h>

#include "TestingPoint.h"

using namespace std;
using namespace Amboss::KML;

TEST( KMLFolder , defaultConstruction )
{
    Folder f;
    EXPECT_EQ( f.data().size() , 0 );
}

TEST( KMLFolder , copyConstruction )
{
    Folder f1;
    f1.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    EXPECT_EQ( f1.data().size() , 1 );
    Folder f2( f1 );
    EXPECT_EQ( f2.data().size() , 1 );
}

TEST( KMLFolder , constructionName )
{
    Folder f1( "Folder" );
    EXPECT_EQ( f1.name() , "Folder" );
}

TEST( KMLFolder , assignment )
{
    Folder f1;
    f1.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    EXPECT_EQ( f1.data().size() , 1 );
    Folder f2;
    f2 = f1;
    EXPECT_EQ( f2.data().size() , 1 );
}

TEST( KMLFolder , setName )
{
    Folder f1;
    f1.name() = "Folder";
    EXPECT_EQ( f1.name() , "Folder" );
}


TEST( KMLFolder , writeOnePlacemark )
{
    Folder f;
    f.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    ostringstream str;
    writeFeature( str , f , 0 );

    string cmp = 
        "<Folder>\n"
        "  <Placemark>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLFolder , writeOnePlacemarkWithFolderName )
{
    Folder f( "Folder" );
    f.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    ostringstream str;
    writeFeature( str , f , 0 );

    string cmp = 
        "<Folder>\n"
        "  <name>Folder</name>\n"
        "  <Placemark>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}

TEST( KMLFolder , writeTwoPlacemarks )
{
    Folder f;
    f.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    f.add( Placemark( TestingPoint( 20.0 , 20.0 ) ) );
    ostringstream str;
    writeFeature( str , f , 0 );

    string cmp = 
        "<Folder>\n"
        "  <Placemark>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "  <Placemark>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        20,20,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLFolder , writeFolder )
{
    Folder f( "Subfolder") ;
    f.add( Placemark( TestingPoint( 10.0 , 10.0 ) ) );
    f.add( Placemark( TestingPoint( 20.0 , 20.0 ) ) );
    Folder f2( "Folder" );
    f2.add( f );
    ostringstream str;
    writeFeature( str , f2 , 0 );

    string cmp = 
        "<Folder>\n"
        "  <name>Folder</name>\n"
        "  <Folder>\n"
        "    <name>Subfolder</name>\n"
        "    <Placemark>\n"
        "      <Point>\n"
        "        <coordinates>\n"
        "          10,10,0 \n"
        "        </coordinates>\n"
        "      </Point>\n"
        "    </Placemark>\n"
        "    <Placemark>\n"
        "      <Point>\n"
        "        <coordinates>\n"
        "          20,20,0 \n"
        "        </coordinates>\n"
        "      </Point>\n"
        "    </Placemark>\n"
        "  </Folder>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLFolder , makeFolder )
{
    ostringstream str;
    writeFeature( str , makeFolder( Placemark( TestingPoint( 10.0 , 10.0 ) ) ) , 0 );

    string cmp = 
        "<Folder>\n"
        "  <Placemark>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLFolder , makeFolderFromGeometryContainer )
{
    ostringstream str;
    std::vector< TestingPoint > tp;
    tp.push_back( TestingPoint( 10.0 , 10.0 ) );
    tp.push_back( TestingPoint( 20.0 , 20.0 ) );
    writeFeature( str , makeFolderFromGeometry( tp.begin() , tp.end() , "Folder" , "PM" ) , 0 );

    string cmp = 
        "<Folder>\n"
        "  <name>Folder</name>\n"
        "  <Placemark>\n"
        "    <name>PM</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "  <Placemark>\n"
        "    <name>PM</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        20,20,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}


TEST( KMLFolder , makeFolderFromGeometryRange )
{
    ostringstream str;
    std::vector< TestingPoint > tp;
    tp.push_back( TestingPoint( 10.0 , 10.0 ) );
    tp.push_back( TestingPoint( 20.0 , 20.0 ) );
    writeFeature( str , makeFolderFromGeometryRange( tp , "Folder" , "PM" ) , 0 );

    string cmp = 
        "<Folder>\n"
        "  <name>Folder</name>\n"
        "  <Placemark>\n"
        "    <name>PM</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        10,10,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "  <Placemark>\n"
        "    <name>PM</name>\n"
        "    <Point>\n"
        "      <coordinates>\n"
        "        20,20,0 \n"
        "      </coordinates>\n"
        "    </Point>\n"
        "  </Placemark>\n"
        "</Folder>\n";

    EXPECT_EQ( cmp , str.str() );
}
