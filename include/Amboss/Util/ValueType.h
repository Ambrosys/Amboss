/*
 * ValueType.h
 * Date: 2012-08-14
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_VALUETYPE_H_INCLUDED
#define AMBOSS_VALUETYPE_H_INCLUDED

#include <memory>
#include <stdexcept>
#include <type_traits>

#ifdef AMB_DEBUG
#include <iostream>
#include <typeinfo>
#endif

namespace Amboss {
namespace Util {


    class ValueType
    {
    public:

        ValueType( void ) noexcept
            : value_()
        {
            #ifdef AMB_DEBUG
            std::cout << "ValueType::ValueType()" << std::endl;
            #endif
        }

        ValueType( const ValueType &t )
            : value_( t.value_->copy() )
        {
            #ifdef AMB_DEBUG
            std::cout << "ValueType::ValueType( const ValueType & )" << std::endl;
            #endif
        }

        ValueType( ValueType &&t ) noexcept
            : value_( t.value_.get() )
        {
            t.value_.reset();
            #ifdef AMB_DEBUG
            std::cout << "ValueType::ValueType( ValueType && )" << std::endl;
            #endif
        }

        template< class T >
        ValueType( const T& t )
            : value_( new ValueModel< T >( t ) )
        {
            #ifdef AMB_DEBUG
            std::cout << "ValueType::ValueType( const T& ) with T = " << typeid( T ).name() << std::endl;
            #endif
        }

        template< class T >
        ValueType( T &&t )
            : value_( new ValueModel< typename std::remove_reference< T >::type >( std::move( t ) ) )
        {
            #ifdef AMB_DEBUG
            std::cout << "ValueType::ValueType( T && ) with T = " << typeid( T ).name() << std::endl;
            #endif
        }


        template< class T >
        ValueType& operator=( const T &t )
        {
            this->value_.reset( new ValueModel< T >( t ) );;
            return *this;
        }

        ValueType& operator=( const ValueType &t )
        {
            this->value_.reset( t.value_->copy() );
            return *this;
        }

        ValueType& operator=( ValueType &&t ) noexcept
        {
            this->value_.reset( t.value_.get() );
            t.value_.reset();
            return *this;
        }

        bool empty( void ) const
        {
            return !bool( value_ );
        }

        template< class T >
        bool sameType( void ) const
        {
            if( !empty() ) return type() == typeid( T );
            else return false;
        }
        
        bool sameType( const ValueType &v1 ) const
        {
            if( !empty() ) return this->type() == v1.type();
            else return false;
        }

        const std::type_info& type( void ) const
        {
            return value_->type();
        }

        ValueType& swap( ValueType &t )
        {
            this->value_.swap( t.value_ );
            return *this;
        }

        template< class T >
        T as( void ) const
        {
            if( sameType< T >() ) 
            {
                const ValueModel< T > *tmp = dynamic_cast< const ValueModel< T >* >( value_.get() );
                return tmp->t_;
            }
            throw std::runtime_error(
                std::string( "ValueType: Wrong type " ) + typeid( T ).name() + " requested for conversion in ValueType::as" );
        }

        template< class T >
        T as( const T &def ) const
        {
            if( sameType< T >() )
                return as< T >();
            else 
                return def;
        }

    private:

        struct ValueInterface {
            virtual const std::type_info& type( void ) const = 0;
            virtual ValueInterface* copy( void ) const = 0;
        };

        template< class T >
        struct ValueModel : public ValueInterface {
            ValueModel( const T& t ) : t_( t )
            {
                #ifdef AMB_DEBUG
                std::cout << "ValueModel< T >::ValueModel< T >( const T & ) with T = " << typeid( T ).name() << std::endl;
                #endif
            }
            ValueModel( T&& t ) : t_( std::move( t ) )
            {
                #ifdef AMB_DEBUG
                std::cout << "ValueModel< T >::ValueModel< T >( T && ) with T = " << typeid( T ).name() << std::endl;
                #endif
            }
            const std::type_info& type( void ) const { return typeid( T ); }
            virtual ValueInterface* copy( void ) const { return new ValueModel< T >( t_ ); }
            T t_;
        };

        std::unique_ptr< ValueInterface > value_;
    };

    // static_assert( std::is_nothrow_default_constructible< ValueType >::value , "is_nothrow_default_constructible" );
    // static_assert( std::is_copy_constructible< ValueType >::value, "is_copy_constructible" );
    // static_assert( std::is_copy_assignable< ValueType >::value, "is_copy_assignable" );
    // static_assert( std::is_nothrow_move_constructible< ValueType >::value, "is_nothrow_move_constructible" );
    // static_assert( std::is_nothrow_move_assignable< ValueType >::value, "is_nothrow_move_assignable" );
    // static_assert( std::is_nothrow_destructible< ValueType >::value, "is_nothrow_destructible" );




} // namespace Util
} // namespace Amboss


#endif // AMBOSS_VALUETYPE_H_INCLUDED
