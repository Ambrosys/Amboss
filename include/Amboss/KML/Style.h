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

    Style( void ) 
        : id_( "" ) ,
          iconStyle_() , lineStyle_() , polyStyle_() , labelStyle_()
    { }

    Style( const std::string &id ,
           const IconStyle &is = IconStyle() , const LineStyle &ls = LineStyle() ,
           const PolyStyle &ps = PolyStyle() , const LabelStyle &las = LabelStyle() )
        : id_( id ) ,
          iconStyle_( is ) , lineStyle_( ls ) , polyStyle_( ps ) , labelStyle_( las )
    { }

    Style( const IconStyle &is , const LineStyle &ls = LineStyle() ,
           const PolyStyle &ps = PolyStyle() , const LabelStyle &las = LabelStyle() )
        : id_( "" ) ,
          iconStyle_( is ) , lineStyle_( ls ) , polyStyle_( ps ) , labelStyle_( las )
    { }



    explicit operator bool( void ) const
    {
        return ( id_ != "" ) || bool( iconStyle_ ) || bool( lineStyle_ ) || bool( polyStyle_ ) || bool( labelStyle_ ) ;
//        return iconStyle_ || lineStyle_ || polyStyle_ || labelStyle_ || ballonStyle_ || listStyle_ ;
    }


    void write( std::ostream &out , size_t indent ) const
    {
        if( *this )
        {
            if( id_ == "" )
                out << getIndent( indent ) << "<Style>" << "\n";
            else
                out << getIndent( indent ) << "<Style id=\"" << id_ << "\">" << "\n";
            iconStyle_.write( out , indent + 1 );
            lineStyle_.write( out , indent + 1 );
            polyStyle_.write( out , indent + 1 );
            labelStyle_.write( out , indent + 1 );
            // ballonStyle_.write( out , indent + 1 );
            // listStyle_.write( out , indent + 1 );
            out << getIndent( indent ) << "</Style>" << "\n";
        }
    }

    const std::string& id( void ) const { return id_; }
    std::string& id( void ) { return id_; }


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

    std::string id_;
    IconStyle iconStyle_;
    LineStyle lineStyle_;
    PolyStyle polyStyle_;
    LabelStyle labelStyle_;
    // BallonStyle ballonStyle_;
    // ListStyle listStyle_;
};


inline bool operator==( const Style &s1 , const Style &s2 )
{
    return
        ( s1.id() == s2.id() ) &&
        ( s1.iconStyle() == s2.iconStyle() ) &&
        ( s1.lineStyle() == s2.lineStyle() ) &&
        ( s1.polyStyle() == s2.polyStyle() ) &&
        ( s1.labelStyle() == s2.labelStyle() );
}

inline bool operator!=( const Style &s1 , const Style &s2 )
{
    return !( s1 == s2 );
}
    


} // namespace KML
} // namespace Amboss


#endif // AMBOSS_STYLE_H_INCLUDED
