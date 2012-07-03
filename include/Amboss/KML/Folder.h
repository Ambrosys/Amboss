/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */


#ifndef AMBOSS_KML_FOLDER_H_INCLUDED
#define AMBOSS_KML_FOLDER_H_INCLUDED

#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <Amboss/KML/Entity.h>
#include <Amboss/KML/WriterHelper.h>

namespace Amboss {
namespace KML {

class Folder
{
public:

    typedef std::vector< Entity > ContainerType;

    template< class T >
    void add( T t , const std::string &name = std::string( "" ) )
    {
        data_.push_back( Entity( t , name ) );
    }

    ContainerType& data( void ) { return data_; }
    const ContainerType& data( void ) const { return data_; }

private:

    std::vector< Entity > data_;
};

template<>
struct WriteObject< Folder >
{
    static void write( std::ostream &out , const Folder &data , size_t indent , const std::string &name )
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

template< class Iter >
Folder makeFolder( Iter first , Iter last , const std::string &name = std::string( "" ) )
{
    Folder f;
    while( first != last ) f.add( *first++ , name );
    return f;
}

template< class R >
Folder makeFolderFromRange( const R &r , const std::string &name = std::string( "" ) )
{
    return makeFolder( boost::const_begin( r ) , boost::const_end( r ) , name );
}

template< class T >
Folder makeFolder( T t , const std::string &name = std::string( "" ) )
{
    Folder f;
    f.add( t , name );
    return f;
}



} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_FOLDER_H_INCLUDED
