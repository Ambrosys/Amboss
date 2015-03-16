/*
 * FunctionWrapper.h
 * Date: 2013-06-14
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FUNCTIONWRAPPER_H_INCLUDED
#define AMBOSS_FUNCTIONWRAPPER_H_INCLUDED

#include <Amboss/Util/AmbossException.h>

#include <memory>
#include <stdexcept>

namespace Amboss {
namespace Thread {

class FunctionWrapper
{
public:
    
    FunctionWrapper() = default;

    template<typename F>
    FunctionWrapper( F&& f )
        : impl( new Model< F >( std::move( f ) ) ) {}

    FunctionWrapper( FunctionWrapper&& other )
        : impl( std::move( other.impl ) ) {}


    FunctionWrapper& operator=( FunctionWrapper&& other )
    {
        impl = std::move( other.impl );
        return *this;
    }

    FunctionWrapper( const FunctionWrapper& ) = delete;
    FunctionWrapper( FunctionWrapper& ) = delete;
    FunctionWrapper& operator=( const FunctionWrapper& ) = delete;
    
    void operator()( void ) const
    {
        if( impl ) impl->call();
        else throw Amboss::Util::AmbossException( "FunctionWrapper::operator() : no function passed" );
    }
    
    operator bool( void ) const { return static_cast< bool >( impl ); }

private:

    struct Concept {
        virtual void call( void ) = 0;
        virtual ~Concept( void ) {}
    };

    template<typename F>
    struct Model : Concept
    {
        F f;
        Model( F&& f_ ) : f( std::move( f_ ) ) {}
        void call( void ) { f(); }
    };

    std::unique_ptr< Concept > impl;
};



} // namespace Thread
} // namespace Amboss


#endif // AMBOSS_FUNCTIONWRAPPER_H_INCLUDED
