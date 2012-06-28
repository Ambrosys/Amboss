/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */


#ifndef AMBOSS_KML_FOLDER_H_INCLUDED
#define AMBOSS_KML_FOLDER_H_INCLUDED

#include <vector>

#include <Amboss/KML/KMLEntity.h>

namespace Amboss {
namespace KML {

class KMLFolder
{
public:

    typedef std::vector< KMLEntity > ContainerType;

    template< class T >
    void add( T t , const std::string &name = std::string( "" ) )
    {
        data_.push_back( KMLEntity( t , name ) );
    }

    ContainerType& data( void ) { return data_; }
    const ContainerType& data( void ) const { return data_; }

private:

    std::vector< KMLEntity > data_;
};

template< class T >
KMLFolder makeFolder( T t , const std::string &name = std::string( "" ) )
{
    KMLFolder f;
    f.add( t , name );
    return f;
}

template< class Iter >
KMLFolder makeFolder( Iter first , Iter last , const std::string &name = std::string( "" ) )
{
    KMLFolder f;
    while( first != last ) f.add( *first++ , name );
    return f;
}

template<>
struct WriteKMLObject< KMLFolder >
{
    static void write( std::ostream &out , const KMLFolder &data , size_t indent , const std::string &name )
    {
        out << getIndent( indent ) << "<Folder>" << "\n";
        if( name != "" ) out << getIndent( indent + 1 ) << "<name>" << name << "</name>" << "\n";
        for( auto e : data.data() )
        {
            e.write( out , indent + 1 );
        }
        out << getIndent( indent ) << "</Folder>" << "\n";
    }
};

} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_FOLDER_H_INCLUDED
