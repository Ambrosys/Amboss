/*
 * ElementWithName.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_ELEMENTWITHNAME_H_INCLUDED
#define AMBOSS_ELEMENTWITHNAME_H_INCLUDED

#include <ostream>
#include <string>

#include <Amboss/KML/WriterHelper.h>


namespace Amboss {
namespace KML {


class ElementWithName
{
public:

    ElementWithName( void ) : name_( "" ) { }
    ElementWithName( const std::string &name ) : name_( name ) { }

    const std::string& name( void ) const { return name_; }
    std::string& name( void ) { return name_; }

    void writeName( std::ostream& out , size_t indent ) const
    {
        if( name_ != "" )
            out << getIndent( indent ) << "<name>" << name_ << "</name>" << "\n";
    }


protected:

    std::string name_;
};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_ELEMENTWITHNAME_H_INCLUDED
