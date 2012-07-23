/*
 * ElementWithStyleTest.cpp
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

#include <Amboss/KML/ElementWithStyle.h>

using namespace Amboss::KML;
using namespace std;


TEST( KMLElementWithStyle , testConstruction )
{
    ElementWithStyle s1;
    ElementWithStyle s2( Style( "id" ) );
}

TEST( KMLElementWithStyle , testEmptyWrite )
{
    ElementWithStyle s;
    ostringstream str;
    s.writeStyle( str , 0 );
    EXPECT_EQ( str.str() , "" );

    ostringstream str2;
    s.writeStyle( str2 , 1 );
    EXPECT_EQ( str2.str() , "" );
}

TEST( KMLElementWithStyle , testWrite )
{
    ElementWithStyle s1( Style( "id" ) );
    ostringstream str;
    s1.writeStyle( str , 0 );
    std::string cmp =
        "<Style id=\"id\">\n"
        "</Style>\n";
    EXPECT_EQ( str.str() , cmp );

    ostringstream str2;
    s1.writeStyle( str2 , 1 );
    std::string cmp2 =
        "  <Style id=\"id\">\n"
        "  </Style>\n";
    EXPECT_EQ( str2.str() , cmp2 );
}

TEST( KMLElementWithStyle , testMultipleWrite )
{
    ElementWithStyle s1( Style( "id1" ) );
    s1.styles().push_back( Style( "id2" ) );
    ostringstream str;
    s1.writeStyle( str , 0 );
    std::string cmp =
        "<Style id=\"id1\">\n"
        "</Style>\n"
        "<Style id=\"id2\">\n"
        "</Style>\n";
    EXPECT_EQ( str.str() , cmp );
}
