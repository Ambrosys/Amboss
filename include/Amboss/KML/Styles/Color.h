/*
 * Color.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_COLOR_H_INCLUDED
#define AMBOSS_COLOR_H_INCLUDED

#include <array>
#include <string>
#include <sstream>


namespace Amboss {
namespace KML {

enum GlobalColor
{
    White , Black , Red , Green , Blue , Yellow
};

class Color
{
public:

    Color( void ) : color_() { }
    Color( unsigned char r , unsigned char g , unsigned char b ) : color_( {{ 255 , r , g , b }} ) { }
    Color( unsigned char r , unsigned char g , unsigned char b , unsigned char a ) : color_( {{ a , r , g , b }} ) { }
    Color( const GlobalColor &c ) : color_()
    {
        switch( c )
        {
        case White : color_ = {{ 255, 0 , 0 , 0 }}; break;
        case Black : color_ = {{ 255, 255 , 255 , 255 }}; break;
        case Red : color_ = {{ 255, 255 , 0 , 0 }}; break;
        case Green : color_ = {{ 255, 0 , 255 , 0 }}; break;
        case Blue : color_ = {{ 255, 0 , 0 , 255 }}; break;
        case Yellow : color_ = {{ 255, 255 , 255 , 0 }}; break;
        }
    }

    unsigned char alpha( void ) const { return color_[0]; }
    unsigned char red( void ) const { return color_[1]; }
    unsigned char green( void ) const { return color_[2]; }
    unsigned char blue( void ) const { return color_[3]; }

    unsigned char& alpha( void ) { return color_[0]; }
    unsigned char& red( void ) { return color_[1]; }
    unsigned char& green( void ) { return color_[2]; }
    unsigned char& blue( void ) { return color_[3]; }


    std::string kmlString( void ) const
    {
        using namespace std;
        ostringstream str;
        str << hex << setw(2) << setfill('0') << int( color_[0] );
        str << hex << setw(2) << setfill('0') << int( color_[1] );
        str << hex << setw(2) << setfill('0') << int( color_[2] );
        str << hex << setw(2) << setfill('0') << int( color_[3] );
        return str.str();
    }

private:

    std::array< unsigned char , 4 > color_;
};

inline bool operator==( const Color &c1 , const Color &c2 )
{
    return
        ( c1.alpha() == c2.alpha() ) &&
        ( c1.red() == c2.red() ) &&
        ( c1.green() == c2.green() ) &&
        ( c1.blue() == c2.blue() );
}

inline bool operator!=( const Color &c1 , const Color &c2 )
{
    return !( c1 == c2 );
}



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_COLOR_H_INCLUDED
