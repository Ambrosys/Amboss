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
#include <vector>

#include <Amboss/KML/WriterHelper.h>

namespace Amboss {
namespace KML {


class ElementWithStyleUrl
{
public:

    typedef std::vector< std::string > UrlSequence;

    ElementWithStyleUrl( void ) : urls_() { }
    ElementWithStyleUrl( const std::string &url ) : urls_( 1 , url ) { }

    const UrlSequence& urls( void ) const { return urls_; }
    UrlSequence& urls( void ) { return urls_; }

    inline void writeStyleUrl( std::ostream& out , size_t indent ) const
    {
        for( size_t i=0 ; i<urls_.size() ; ++i )
        {
            if( urls_[i] != "" )
                out << getIndent( indent ) << "<styleUrl>" << urls_[i] << "</styleUrl>" << "\n";
        }
    }


private:

    UrlSequence urls_;
};




} // namespace KML
} // namespace Amboss


#endif // AMBOSS_ELEMENTWITHSTYLEURL_H_INCLUDED
