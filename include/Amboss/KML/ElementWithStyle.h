/*
 * ElementWithStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_ELEMENTWITHSTYLE_H_INCLUDED
#define AMBOSS_ELEMENTWITHSTYLE_H_INCLUDED

#include <vector>

#include <Amboss/KML/WriterHelper.h>
#include <Amboss/KML/Style.h>

namespace Amboss {
namespace KML {


class ElementWithStyle
{
public:

    typedef std::vector< Style > StyleSequence;

    ElementWithStyle(  void ) : styles_() { }
    ElementWithStyle( const Style &style ) : styles_( 1 , style ) { }

    const StyleSequence& styles( void ) const { return styles_; }
    StyleSequence& styles( void ) { return styles_; }

    void writeStyle( std::ostream &out , size_t indent ) const
    {
        for( size_t i=0 ; i<styles_.size() ; ++i )
            styles_[i].write( out , indent );
    }

private:

    StyleSequence styles_;
};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_ELEMENTWITHSTYLE_H_INCLUDED
