/*
 * ElementWithNameTest.cpp
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

#include <Amboss/KML/ElementWithName.h>

using namespace Amboss::KML;
using namespace std;

TEST( KMLElementWithName , testConstruction )
{
    ElementWithName el;
    EXPECT_EQ( el.name() , "" );

    ElementWithName el2( "Name" );
    EXPECT_EQ( el2.name() , "Name" );
}

TEST( KMLElementWithName , testSetName )
{
    ElementWithName el;
    el.name() = "Name";
    EXPECT_EQ( el.name() , "Name" );
}

TEST( KMLElementWithName , testWriteEmptyElement )
{
    ElementWithName el;
    ostringstream str;
    el.writeName( str , 0 );
    EXPECT_EQ( str.str() , "" );

    el.writeName( str , 1 );
    EXPECT_EQ( str.str() , "" );
}

TEST( KMLElementWithName , testWriteElement )
{
    ElementWithName el( "Name" );
    ostringstream str;
    el.writeName( str , 0 );
    EXPECT_EQ( str.str() , "<name>Name</name>\n" );

    ostringstream str2;
    el.writeName( str2 , 1 );
    EXPECT_EQ( str2.str() , "  <name>Name</name>\n" );
}
