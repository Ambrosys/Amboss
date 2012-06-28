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

#include <Amboss/KML/KMLEntity.h>
#include <Amboss/KML/KMLWriterHelper.h>

namespace Amboss {
namespace KML {



class KMLWriter
{
public:

    template< class T >
    void add( T t , const std::string &name = "" )
    {
	objects_.push_back( KMLEntity( t , name ) );
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

    std::vector< KMLEntity > objects_;

};

} // namespace KML
} // namespace Amboss


#endif // AMBOSS_KML_WRITER_H_INCLUDED
