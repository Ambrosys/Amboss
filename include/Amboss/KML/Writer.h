/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */

#ifndef AMBOSS_KML_WRITER_H_INCLUDED
#define AMBOSS_KML_WRITER_H_INCLUDED

#include <fstream>
#include <vector>
#include <memory>
#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/for_each.hpp> 

#include <Amboss/KML/Entity.h>
#include <Amboss/KML/WriterHelper.h>

namespace Amboss {
namespace KML {



class Writer
{
public:

    template< class T >
    void add( T t , const std::string &name = "" )
    {
	objects_.push_back( Entity( t , name ) );
    }

    void write( const std::string &fn ) const
    {
	std::ofstream fout( fn.c_str() );
        fout.precision( 14 );
	write( fout );
    }

    void write( std::ostream &out ) const
    {
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << "\n";
	out << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << "\n";
	out << "<Document>" << "\n";

	for( auto obj : objects_ )
	{
	    obj.write( out , 1 );
	}

	out << "</Document>" << "\n";
	out << "</kml>" << "\n";
    }

private:

    std::vector< Entity > objects_;
};

template< class T >
void write( std::ostream &out , T t , const std::string& name = "" )
{
    Writer writer;
    writer.add( t , name );
    writer.write( out );
}


template< class T >
void write( const std::string &filename , T t , const std::string& name = "" )
{
    std::ofstream fout( filename.c_str() );
    write( t , fout , name );
}

namespace Detail {

    struct AddToWriter
    {
        Writer &writer_;
        AddToWriter( Writer &writer ) : writer_( writer ) { }
        template< class T > void operator()( T t ) { writer_.add( t ); }
    };
}

template< class R >
void writeRange( std::ostream &out , const R &r )
{
    Writer writer;
    boost::for_each( r , Detail::AddToWriter( writer ) );
    writer.write( out );
}

template< class R >
void writeRange( const std::string &filename , const R &r )
{
    std::ofstream fout( filename.c_str() );
    fout.precision( 14 );
    writeRange( fout , r );
}


} // namespace KML
} // namespace Amboss


#endif // AMBOSS_KML_WRITER_H_INCLUDED
