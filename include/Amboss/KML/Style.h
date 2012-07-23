/*
 * Style.h
 * Date: 2012-07-23
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_STYLE_H_INCLUDED
#define AMBOSS_STYLE_H_INCLUDED

#include <Amboss/KML/Styles/IconStyle.h>
#include <Amboss/KML/Styles/LineStyle.h>
#include <Amboss/KML/Styles/PolyStyle.h>
#include <Amboss/KML/Styles/LabelStyle.h>
// #include <Amboss/KML/Styles/BallonStyle.h>
// #include <Amboss/KML/Styles/ListStyle.h>


namespace Amboss {
namespace KML {




class Style
{
public:


    explicit operator bool( void ) const
    {
        return iconStyle_ || lineStyle_ || polyStyle_ || labelStyle_ ;
//        return iconStyle_ || lineStyle_ || polyStyle_ || labelStyle_ || ballonStyle_ || listStyle_ ;
    }


    void write( std::ostream &out , size_t indent ) const
    {
        if( *this )
        {
            out << getIndent( indent ) << "<Style>" << "\n";
            iconStyle_.write( out , indent + 1 );
            lineStyle_.write( out , indent + 1 );
            polyStyle_.write( out , indent + 1 );
            labelStyle_.write( out , indent + 1 );
            // ballonStyle_.write( out , indent + 1 );
            // listStyle_.write( out , indent + 1 );
            out << getIndent( indent ) << "</Style>" << "\n";
        }
    }

    const IconStyle& iconStyle( void ) const { return iconStyle_; }
    IconStyle& iconStyle( void ) { return iconStyle_; }

    const LineStyle& lineStyle( void ) const { return lineStyle_; }
    LineStyle& lineStyle( void ) { return lineStyle_; }

    const PolyStyle& polyStyle( void ) const { return polyStyle_; }
    PolyStyle& polyStyle( void ) { return polyStyle_; }

    const LabelStyle& labelStyle( void ) const { return labelStyle_; }
    LabelStyle& labelStyle( void ) { return labelStyle_; }

    // const BallonStyle& ballonStyle( void ) const { return ballonStyle_; }
    // BallonStyle& ballonStyle( void ) { return ballonStyle_; }

    // const ListStyle& listStyle( void ) const { return listStyle_; }
    // ListStyle& listStyle( void ) { return listStyle_; }

 
private:

    IconStyle iconStyle_;
    LineStyle lineStyle_;
    PolyStyle polyStyle_;
    LabelStyle labelStyle_;
    // BallonStyle ballonStyle_;
    // ListStyle listStyle_;
};





} // namespace KML
} // namespace Amboss


#endif // AMBOSS_STYLE_H_INCLUDED
