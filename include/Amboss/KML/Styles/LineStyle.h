/*
 * LineStyle.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LINESTYLE_H_INCLUDED
#define AMBOSS_LINESTYLE_H_INCLUDED

#include <Amboss/KML/Styles/ColorStyle.h>
#include <Amboss/KML/WriterHelper.h>


namespace Amboss {
namespace KML {


/*
 * ToDo : add missing attributes
 */
class LineStyle
{
public:

    LineStyle( void )
        : isSet_( false ) , colorStyle_() , width_( 1.0 ) 
          // , outerColor() , outerWidth_( 0.0 ) ,
          // physicalWidth_( 0.0 ) , labelVisibility_( false )
    { }

    LineStyle( const ColorStyle &colorStyle , double width = 1.0 )
        : isSet_( true ) , colorStyle_( colorStyle ) , width_( width )
        // , outerColor() , outerWidth_( 0.0 ) ,
        //   physicalWidth_( 0.0 ) , labelVisibility_( false )
    { }

    explicit operator bool( void ) const
    {
        return isSet_;
    }

    const ColorStyle& colorStyle( void ) const { return colorStyle_; }
    ColorStyle& colorStyle( void ) { isSet_ = true ; return colorStyle_; }

    double width( void ) const { return width_; }
    double& width( void ) { isSet_ = true ; return width_; }

    void reset( void ) { isSet_ = false; }

    void write( std::ostream &out , size_t indent ) const
    {
        if( bool( *this ) )
        {
            out << getIndent( indent ) << "<LineStyle>" << "\n";
            colorStyle_.write( out , indent + 1 );
            out << getIndent( indent + 1 ) << "<width>" << width_ << "</width>" << "\n";
            out << getIndent( indent ) << "</LineStyle>" << "\n";
        }
    }

private:

    bool isSet_;
    ColorStyle colorStyle_;
    double width_;
    // Color outerColor_;
    // double outerWidth_;
    // double physicalWidth_;
    // bool labelVisibility_;
    

};



} // namespace KML
} // namespace Amboss


#endif // AMBOSS_LINESTYLE_H_INCLUDED
