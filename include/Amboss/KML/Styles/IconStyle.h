/*
 * IconStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_ICONSTYLE_H_INCLUDED
#define AMBOSS_ICONSTYLE_H_INCLUDED

#include <Amboss/KML/Styles/ColorStyle.h>


namespace Amboss {
namespace KML {

enum DefaultIcons
{
    ShadedDot ,     // "http://maps.google.com/mapfiles/kml/shapes/shaded_dot.png"
    Paddle ,        // "http://maps.google.com/mapfiles/kml/paddle/wht-blank.png"
    PushPin         // "http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png"
};

inline std::string getDefaultIconUrl( DefaultIcons icon )
{
    switch( icon )
    {
    case ShadedDot : return "http://maps.google.com/mapfiles/kml/shapes/shaded_dot.png"; break;
    case Paddle : return "http://maps.google.com/mapfiles/kml/paddle/wht-blank.png"; break;
    case PushPin : return "http://maps.google.com/mapfiles/kml/pushpin/wht-pushpin.png"; break;
    }
};


/*
 * ToDo : add hotSpot
 */

class IconStyle
{
public:

    IconStyle( void ) : isSet_( false ) , colorStyle_() , scale_( 1.0 ) , iconRef_() { }
    IconStyle( const ColorStyle colorStyle , double scale , const std::string &iconRef )
        : isSet_( true ) , colorStyle_( colorStyle ) , scale_( scale ) , iconRef_( iconRef ) { }
    IconStyle( const ColorStyle colorStyle , double scale , DefaultIcons icon )
        : isSet_( true ) , colorStyle_( colorStyle ) , scale_( scale ) , iconRef_( getDefaultIconUrl( icon ) ) { }


    explicit operator bool( void ) const
    {
        return isSet_;
    }

    const ColorStyle& colorStyle( void ) const { return colorStyle_; }
    ColorStyle& colorStyle( void ) { isSet_ = true ; return colorStyle_; }
    double scale( void ) const { return scale_; }
    double& scale( void ) { isSet_ = true ; return scale_; }
    const std::string& iconRef( void ) const { return iconRef_; }
    std::string& iconRef( void ) { isSet_ = true ; return iconRef_; }

    void setIconRef( const std::string &iconRef ) { isSet_ = true ; iconRef_ = iconRef; }
    void setIconRef( DefaultIcons icon ) { isSet_ = true ; iconRef_ = getDefaultIconUrl( icon ); }

    void write( std::ostream &out , size_t indent ) const
    {
        if( bool( *this ) )
        {
            out << getIndent( indent ) << "<IconStyle>" << "\n";
            colorStyle_.write( out , indent + 1 );
            out << getIndent( indent + 1 ) << "<scale>" << scale_ << "</scale>" << "\n";
            out << getIndent( indent + 1 ) << "<Icon><href>" << iconRef_ << "</href></Icon>" << "\n";
            out << getIndent( indent ) << "</IconStyle>" << "\n";
        }
    }

    void reset( void )
    {
        isSet_ = false;
    }

private:

    bool isSet_;
    ColorStyle colorStyle_;
    double scale_;
    std::string iconRef_;

};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_ICONSTYLE_H_INCLUDED
