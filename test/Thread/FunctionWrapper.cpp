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
#include <gmock/gmock.h>

using namespace std;
using namespace Amboss::Thread;

void func( void )
{
}

struct mocker
{
    MOCK_CONST_METHOD0( run , void() );
};

struct mock_functor
{
    mocker &mocker_;
    mock_functor( mocker &m ) : mocker_( m ) { }
    void operator()( void ) const { mocker_.run(); }
};

struct functor
{
    void operator()( void )  { }
};



TEST( FunctionWrapper , defaultConstruct )
{
    FunctionWrapper f;
    ASSERT_THROW( f() , std::runtime_error );
}

TEST( FunctionWrapper , typeConstrcutFromCFunction )
{
    FunctionWrapper f( &func );
    f();
}

TEST( FunctionWrapper , typeConstrcutFromFunctor )
{
    mocker m;
    FunctionWrapper f( ( mock_functor( m ) ) );
    EXPECT_CALL( m , run() )
        .Times( 1 );
    f();
}


TEST( FunctionWrapper , moveConstruct )
{
    mocker m;
    FunctionWrapper f1( ( mock_functor( m ) ) );
    FunctionWrapper f2( std::move( f1 ) );
    EXPECT_CALL( m , run() )
        .Times( 1 );
    f2();
}
