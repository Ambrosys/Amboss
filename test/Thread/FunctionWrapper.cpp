/*
 * FunctionWrapper.cpp
 * Date: 2013-06-15
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <Amboss/Thread/FunctionWrapper.h>

#include <sstream>

#include <gtest/gtest.h>

using namespace std;
using namespace Amboss::Thread;

void func( void )
{
}

struct functor
{
    void operator()( void ) const { }
};

TEST( FunctionWrapper , defaultConstruct )
{
    FunctionWrapper f;
    // f();
}

TEST( FunctionWrapper , typeConstrcutFromCFunction )
{
    FunctionWrapper f( &func );
    f();
}

TEST( FunctionWrapper , typeConstrcutFromFunctor )
{
    FunctionWrapper f( ( functor() ) );
    f();
}


TEST( FunctionWrapper , moveConstruct )
{
    FunctionWrapper f1( &func );
    FunctionWrapper f2( std::move( f1 ) );
    f2();
}
