/*
 * Document.h
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_DOCUMENT_H_INCLUDED
#define AMBOSS_DOCUMENT_H_INCLUDED

#include <Amboss/KML/Feature.h>
#include <Amboss/KML/Placemark.h>
#include <Amboss/KML/WriterHelper.h>
#include <Amboss/KML/ElementWithName.h>
#include <Amboss/KML/ElementWithStyleUrl.h>
#include <Amboss/KML/ElementWithStyle.h>

#include <Amboss/Util/AmbossException.h>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/for_each.hpp> 

#include <fstream>
#include <stdexcept>




namespace Amboss {
namespace KML {

class Document : public ElementWithName , public ElementWithStyleUrl , public ElementWithStyle
{
public:

    typedef std::vector< Feature > SequenceType;

    Document( void )
        : ElementWithName() , ElementWithStyleUrl() , ElementWithStyle() , data_() { }
    Document( const std::string &name )
        : ElementWithName( name ) , ElementWithStyleUrl() , ElementWithStyle() , data_() { }
    Document( const Style &style )
        : ElementWithName() , ElementWithStyleUrl() , ElementWithStyle( style ) , data_() { }
    Document( const Style &style , const std::string &name )
        : ElementWithName( name ) , ElementWithStyleUrl() , ElementWithStyle( style ) , data_() { }

    template< class T >
    void add( T t )
    {
        data_.push_back( Feature( t ) );
    }

    SequenceType& data( void ) { return data_; }
    const SequenceType& data( void ) const { return data_; }

    void write( const std::string &filename )
    {
        std::ofstream fout( filename.c_str() );
        if( !fout.good() ) throw Amboss::Util::AmbossException( std::string( "Amboss::KML::Document::write() : Could not open " ) + filename );
        fout.precision( 14 );
        write( fout );
    }

    void write( std::ostream &out )
    {
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << "\n";
	out << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << "\n";
	out << "<Document>" << "\n";
        writeName( out , 1 );
        writeStyleUrl( out , 1 );
        writeStyle( out , 1 );
	for( const auto &obj : data_ )
	{
            obj.write( out , 1 );
	}
	out << "</Document>" << "\n";
	out << "</kml>" << "\n";
    }


private:

    SequenceType data_;
};





template< class T >
void write( std::ostream &out , T t , const std::string& docname = "" )
{
    Document doc( docname );
    doc.add( t  );
    doc.write( out );
}


template< class T >
void write( const std::string &filename , T t , const std::string& name = "" )
{
    std::ofstream fout( filename.c_str() );
    write( fout , t , name );
}

namespace Detail {

    struct AddToDocument
    {
        Document &doc_;
        AddToDocument( Document &doc ) : doc_( doc ) { }
        template< class T > void operator()( T t ) { doc_.add( t ); }
    };

    struct AddPlacemarkToDocument
    {
        Document &doc_;
        const std::string &pmname_;
        AddPlacemarkToDocument( Document &doc , const std::string pmname ) : doc_( doc ) , pmname_( pmname ) { }
        template< class T > void operator()( T t ) { doc_.add( Placemark( t , pmname_ ) ); }
    };

}

template< class R >
void writeRange( std::ostream &out , const R &r , const std::string &docname = std::string( "" ) )
{
    Document doc( docname );
    boost::for_each( r , Detail::AddToDocument( doc ) );
    doc.write( out );
}

template< class R >
void writePlacemarkRange( std::ostream &out , const R &r , const std::string &docname = std::string( "" ) , const std::string &pmname = std::string( "" ) )
{
    Document doc( docname );
    boost::for_each( r , Detail::AddPlacemarkToDocument( doc , pmname ) );
    doc.write( out );
}


template< class R >
void writeRange( const std::string &filename , const R &r , const std::string &docname = std::string( "" ) )
{
    std::ofstream fout( filename.c_str() );
    fout.precision( 14 );
    writeRange( fout , r , docname );
}

template< class R >
void writePlacemarkRange( const std::string &filename , const R &r , const std::string &docname = std::string( "" ) , const std::string &pmname = std::string( "" ) )
{
    std::ofstream fout( filename.c_str() );
    fout.precision( 14 );
    writePlacemarkRange( fout , r , docname , pmname );
}


} // namespace KML
} // namespace Amboss


#endif // AMBOSS_DOCUMENT_H_INCLUDED
