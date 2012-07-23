/*
 * LabelStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LABELSTYLE_H_INCLUDED
#define AMBOSS_LABELSTYLE_H_INCLUDED

#include <Amboss/KML/Styles/ColorStyle.h>
#include <Amboss/KML/WriterHelper.h>



namespace Amboss {
namespace KML {


class LabelStyle
{
public:

    LabelStyle( void )
        : isSet_( false )
        , colorStyle_() , scale_( 1.0 )
    { }

    LabelStyle( const ColorStyle &colorStyle , double scale = 1.0 )
        : isSet_( true ) 
        , colorStyle_( colorStyle ) , scale_( scale )
    { }


    explicit operator bool( void ) const
    {
        return isSet_;
    }

    const ColorStyle& colorStyle( void ) const { return colorStyle_; }
    ColorStyle& colorStyle( void ) { isSet_ = true ; return colorStyle_; }

    double scale( void ) const { return scale_; }
    double& scale( void ) { isSet_ = true ; return scale_; }


    void write( std::ostream &out , size_t indent ) const
    {
        if( bool( *this ) )
        {
            out << getIndent( indent ) << "<LabelStyle>" << "\n";
            colorStyle_.write( out , indent + 1 );
            out << getIndent( indent + 1 ) << "<scale>" << scale_ << "</scale>" << "\n";
            out << getIndent( indent ) << "</LabelStyle>" << "\n";
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
};

inline bool operator==( const LabelStyle &s1 , const LabelStyle &s2 )
{
    return (
        ( bool( s1 ) == bool( s2 ) ) &&
        ( s1.colorStyle() == s2.colorStyle() ) &&
        ( s1.scale() == s2.scale() )
        );
}

inline bool operator!=( const LabelStyle &s1 , const LabelStyle &s2 )
{
    return !( s1 == s2 );
}


} // namespace KML
} // namespace Amboss


#endif // AMBOSS_LABELSTYLE_H_INCLUDED
