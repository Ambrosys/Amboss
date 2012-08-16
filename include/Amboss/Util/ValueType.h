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

namespace Amboss {
namespace Util {


    class ValueType
    {
    public:

        ValueType( void )
            : value_()
        { }

        template< class T >
        ValueType( const T& t )
            : value_( new ValueModel< T >( t ) )
        { }

        ValueType( const ValueType &t )
            : value_( t.value_->copy() )
        { }

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
            ValueModel( const T& t ) : t_( t ) { }
            const std::type_info& type( void ) const { return typeid( T ); }
            virtual ValueInterface* copy( void ) const { return new ValueModel< T >( t_ ); }
            T t_;
        };

        std::unique_ptr< ValueInterface > value_;
    };





} // namespace Util
} // namespace Amboss


#endif // AMBOSS_VALUETYPE_H_INCLUDED
