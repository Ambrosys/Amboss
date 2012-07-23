/*
 * ColorStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_COLORSTYLE_H_INCLUDED
#define AMBOSS_COLORSTYLE_H_INCLUDED

#include <string>
#include <ostream>

#include <Amboss/KML/Styles/Color.h>
#include <Amboss/KML/WriterHelper.h>


namespace Amboss {
namespace KML {


class ColorStyle
{
public:

    enum ColorMode { normal , random };

    ColorStyle( void ) : color_( White ) , colorMode_( normal ) { }
    ColorStyle( const Color &c ) : color_( c ) , colorMode_( normal ) { }
    ColorStyle( const GlobalColor &c ) : color_( c ) , colorMode_( normal ) { }
    ColorStyle( const Color &c , const ColorMode &colorMode ) : color_( c ) , colorMode_( colorMode ) { }
    ColorStyle( const GlobalColor &c , const ColorMode &colorMode ) : color_( c ) , colorMode_( colorMode ) { }

    const Color& color( void ) const { return color_; }
    Color& color( void ) { return color_; }
    const ColorMode& colorMode( void ) const { return colorMode_; }
    ColorMode& colorMode( void ) { return colorMode_; }

    void write( std::ostream &out , size_t indent ) const
    {
        out << getIndent( indent ) << "<color>" << color_.kmlString() << "</color>" << "\n";
        out << getIndent( indent ) << "<colorMode>" << ( ( colorMode_ == normal ) ? "normal" : "random" ) << "</colorMode>" << "\n";
    }

private:

    Color color_;
    ColorMode colorMode_; 
};

inline bool operator==( const ColorStyle &s1 , const ColorStyle &s2 )
{
    return ( s1.color() == s2.color() ) && ( s1.colorMode() == s2.colorMode() );
}

inline bool operator!=( const ColorStyle &s1 , const ColorStyle &s2 )
{
    return ! ( s1 == s2 );
}



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_COLORSTYLE_H_INCLUDED
