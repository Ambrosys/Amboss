/*
 * StyleUrl.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_ELEMENTWITHSTYLEURL_H_INCLUDED
#define AMBOSS_ELEMENTWITHSTYLEURL_H_INCLUDED

#include <string>

#include <Amboss/KML/WriterHelper.h>

namespace Amboss {
namespace KML {


class ElementWithStyleUrl
{
public:

    ElementWithStyleUrl( void ) : url_( "" ) { }
    ElementWithStyleUrl( const std::string &url ) : url_( url ) { }

    const std::string& url( void ) const { return url_; }
    std::string& url( void ) { return url_; }

    inline void write( std::ostream& out , size_t indent )
    {
        if( url_ != "" )
            out << getIndent( indent ) << "<StyleUrl>" << url_ << "</StyleUrl>" << "\n";
    }


private:

    std::string url_;
};




} // namespace KML
} // namespace Amboss


#endif // AMBOSS_ELEMENTWITHSTYLEURL_H_INCLUDED
