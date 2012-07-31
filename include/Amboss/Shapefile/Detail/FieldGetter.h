/*
 * FieldGetter.h
 * Date: 2012-07-31
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FIELDGETTER_H_INCLUDED
#define AMBOSS_FIELDGETTER_H_INCLUDED

#include <string>
#include <type_traits>

#include <ogrsf_frmts.h>


namespace Amboss {
namespace Shapefile {
namespace Detail {

    template< class T , class Enabler = void >
    struct FieldGetter;

    template< class T >
    struct FieldGetter< T , typename std::enable_if< std::is_integral< T >::value >::type >
    {
        static T getValue( int id , OGRFeature *feature )
        {
            return T();
        }
    };


    template< class T >
    struct FieldGetter< T , typename std::enable_if< std::is_floating_point< T >::value >::type >
    {
        static T getValue( int id , OGRFeature *feature )
        {
            return T();
        }
    };

    template<>
    struct FieldGetter< std::string >
    {
        static std::string getValue( int id , OGRFeature *feature )
        {
            return std::string( feature->GetFieldAsString( id ) );
        }
    };

    // template< class Cont , class Enabler = void >
    // struct is_integral_container : public std::false_type { };

    // template< class Cont , typename std::enable_if< typename std::is_integral< typename Cont::value_type >::type >::type >
    // struct is_integral_container : public std::true_type { };

    // template< class Cont >
    // struct FieldGetter< Cont , std::enable_if< is_integral_container< Cont >::type > >
    // {
    //     static Cont getValue( int id , const OGRFeature *feature )
    //     {
    //         return Cont();
    //     }
    // }




} // namespace Detail
} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_FIELDGETTER_H_INCLUDED
