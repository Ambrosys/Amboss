/*
 * ElementWithStyleUrlTest.cpp
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

#include <Amboss/KML/ElementWithStyleUrl.h>


using namespace std;
using namespace Amboss::KML;


TEST( KMLElementWithStyleUrl , testConstruction )
{
    ElementWithStyleUrl s1;
    EXPECT_EQ( s1.urls().size() , 0 );

    ElementWithStyleUrl s2( "Url" );
    EXPECT_EQ( s2.urls().size() , 1 );
    EXPECT_EQ( s2.urls().front() , "Url" );
}


TEST( KMLElementWithStyleUrl , testEmptyWrite )
{
    ElementWithStyleUrl s1;
    ostringstream str;
    s1.writeStyleUrl( str , 0 );
    EXPECT_EQ( str.str() , "" );

    ostringstream str2;
    s1.writeStyleUrl( str2 , 1 );
    EXPECT_EQ( str2.str() , "" );
}

TEST( KMLElementWithStyleUrl , testWrite )
{
    ElementWithStyleUrl s1( "Url" );
    ostringstream str;
    s1.writeStyleUrl( str , 0 );
    EXPECT_EQ( str.str() , "<styleUrl>Url</styleUrl>\n" );

    ostringstream str2;
    s1.writeStyleUrl( str2 , 1 );
    EXPECT_EQ( str2.str() , "  <styleUrl>Url</styleUrl>\n" );
}
