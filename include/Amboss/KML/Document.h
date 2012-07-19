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

#include <fstream>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/for_each.hpp> 

#include <Amboss/KML/Folder.h>


namespace Amboss {
namespace KML {

class Document : public Folder
{
public:

    Document( void ) : Folder() { }
    Document( const std::string &name ) : Folder( name ) { }

    void write( const std::string &filename )
    {
        std::ofstream fout( filename.c_str() );
        write( fout );
    }
    void write( std::ostream &out );

};


template< >
struct WriteObject< Document >
{
    inline static void write( std::ostream &out , const Document &doc , size_t indent )
    {
	out << getIndent( indent ) << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << "\n";
	out << getIndent( indent ) << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << "\n";
	out << getIndent( indent ) << "<Document>" << "\n";
        if( doc.name() != "" ) out << getIndent( indent +1 ) << "<name>" << doc.name() << "</name>" << "\n";
	for( const auto &obj : doc.data() )
	{
            obj.write( out , indent + 1 );
	}
	out << "</Document>" << "\n";
	out << "</kml>" << "\n";

    }
};

void Document::write( std::ostream &out )
{
    writeObject( out , *this , 0 );
}





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
