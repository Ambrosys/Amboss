/*
 * PolyStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_POLYSTYLE_H_INCLUDED
#define AMBOSS_POLYSTYLE_H_INCLUDED

#include <Amboss/KML/Styles/ColorStyle.h>
#include <Amboss/KML/WriterHelper.h>


namespace Amboss {
namespace KML {


class PolyStyle
{
public:

    PolyStyle( void )
        : isSet_( false )
        , colorStyle_()
    { }

    PolyStyle( const ColorStyle &colorStyle , bool fill = false , bool outline = true )
        : isSet_( true ) 
        , colorStyle_( colorStyle ) , fill_( fill ) , outline_( outline )
    { }

    explicit operator bool( void ) const
    {
        return isSet_;
    }

    const ColorStyle& colorStyle( void ) const { return colorStyle_; }
    ColorStyle& colorStyle( void ) { isSet_ = true ; return colorStyle_; }

    bool fill( void ) const { return fill_; }
    bool& fill( void ) { isSet_ = true ; return fill_; }

    bool outline( void ) const { return outline_; }
    bool& outline( void ) { isSet_ = true ; return outline_; }
    
    void reset( void ) { isSet_ = false; }


    void write( std::ostream &out , size_t indent ) const
    {
        if( bool( *this ) )
        {
            out << getIndent( indent ) << "<PolyStyle>" << "\n";
            colorStyle_.write( out , indent + 1 );
            out << getIndent( indent + 1 ) << "<fill>" << fill_ << "</fill>" << "\n";
            out << getIndent( indent + 1 ) << "<outline>" << outline_ << "</outline>" << "\n";
            out << getIndent( indent ) << "</PolyStyle>" << "\n";
        }
    }

private:

    bool isSet_;
    ColorStyle colorStyle_;
    bool fill_;
    bool outline_;
};


inline bool operator==( const PolyStyle &s1 , const PolyStyle &s2 )
{
    return (
        ( bool( s1 ) == bool( s2 ) ) &&
        ( s1.colorStyle() == s2.colorStyle() ) &&
        ( s1.fill() == s2.fill() ) &&
        ( s1.outline() == s2.outline() )
        );
}

inline bool operator!=( const PolyStyle &s1 , const PolyStyle &s2 )
{
    return !( s1 == s2 );
}


} // namespace KML
} // namespace Amboss


#endif // AMBOSS_POLYSTYLE_H_INCLUDED
