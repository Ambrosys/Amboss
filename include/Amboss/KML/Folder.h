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

#include <Amboss/KML/Geometry.h>
#include <Amboss/KML/Placemark.h>
#include <Amboss/KML/WriterHelper.h>
#include <Amboss/KML/ElementWithName.h>

namespace Amboss {
namespace KML {

class Folder : public ElementWithName
{
public:

    typedef std::vector< Feature > SequenceType;

    Folder( void ) : ElementWithName() , data_() { }
    Folder( const std::string &name ) : ElementWithName( name ) , data_() { }

    template< class T >
    void add( T t )
    {
        data_.push_back( Feature( t ) );
    }

    SequenceType& data( void ) { return data_; }
    const SequenceType& data( void ) const { return data_; }

private:

    SequenceType data_;
};

template<>
struct WriteFeature< Folder >
{
    static void write( std::ostream &out , const Folder &data , size_t indent  )
    {
        out << getIndent( indent ) << "<Folder>" << "\n";
        data.writeName( out , indent + 1 );
        for( auto e : data.data() )
        {
            e.write( out , indent + 1 );
        }
        out << getIndent( indent ) << "</Folder>" << "\n";
    }
};



template< class T  >
Folder makeFolder( T t , const std::string &name = std::string( "" ) )
{
    Folder f( name );
    f.add( t );
    return f;
}


template< class Iter >
Folder makeFolder( Iter first , Iter last , const std::string &name = std::string( "" ) )
{
    Folder f( name );
    while( first != last ) f.add( *first++ );
    return f;
}

template< class Iter >
Folder makeFolderFromGeometry( Iter first , Iter last , const std::string &foldername = std::string( "" ) ,
                               const std::string placemarkname = std::string( "" ) )
{
    Folder f( foldername );
    while( first != last ) f.add( Placemark( *first++ , placemarkname ) );
    return f;
}


template< class R >
Folder makeFolderFromRange( const R &r , const std::string &name = std::string( "" ) )
{
    return makeFolder( boost::const_begin( r ) , boost::const_end( r ) , name );
}

template< class R >
Folder makeFolderFromGeometryRange( const R &r , const std::string &foldername = std::string( "" ) ,
                                     const std::string &placemarkname = std::string( "" ) )
{
    return makeFolderFromGeometry( boost::const_begin( r ) , boost::const_end( r ) , foldername , placemarkname );
}






} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_FOLDER_H_INCLUDED
