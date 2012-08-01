/*
 * FieldDesc.h
 * Date: 2012-07-31
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FIELDDESC_H_INCLUDED
#define AMBOSS_FIELDDESC_H_INCLUDED

#include <ogrsf_frmts.h>

namespace Amboss {
namespace Shapefile {

class FieldDesc
{
public:

    typedef OGRFieldType FieldType;

    FieldDesc( OGRFieldDefn *field )
        : field_( field )
    { }

    std::string name( void ) const { return std::string( field_->GetNameRef() ); }

    FieldType type( void ) const { return field_->GetType(); }
    std::string typeName( void ) const { return OGRFieldDefn::GetFieldTypeName( type() ); }

private:

    OGRFieldDefn *field_;
};

inline FieldDesc makeFieldDesc( OGRFieldDefn *field )
{
    return FieldDesc( field );
}



} // namespace Shapefile
} // namespace Amboss


#endif // AMBOSS_FIELDDESC_H_INCLUDED
