/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */

#ifndef AMBOSS_KML_ENTITY_H_INCLUDED
#define AMBOSS_KML_ENTITY_H_INCLUDED

#include <ostream>
#include <memory>
#include <string>
#include <type_traits>

namespace Amboss {
namespace KML {



template< class T >
struct WriteKMLObject ;



template< class T >
inline void writeKMLObject( std::ostream &out , const T &t , size_t indent , const std::string &name )
{
    WriteKMLObject< T >::write( out , t , indent , name );
}


class KMLEntity
{
public:

    KMLEntity( void ) : object_( nullptr ) { }

    template< class T >
    KMLEntity( T t , const std::string &name = std::string( "" ) ) : object_( new WriteableModel< T >( t , name ) ) { }

    KMLEntity( const KMLEntity &e ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }

    ~KMLEntity( void ) { }

    const KMLEntity& operator=( const KMLEntity &e ) {
        object_.reset( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) ;
        return *this;
    }

    void write( std::ostream &out , size_t indent ) const {
        object_->write( out , indent );
    }

private:

    struct WriteableConcept
    {
	virtual ~WriteableConcept( void ) { };
	virtual void write( std::ostream &out , size_t indent ) const = 0;
        virtual WriteableConcept* copy( void ) const = 0;
    };

    template< class T >
    struct WriteableModel : public WriteableConcept
    {
	WriteableModel( T t , const std::string &name ) : data_( t ) , name_( name ) { }
	~WriteableModel( void ) { }
	void write( std::ostream &out , size_t indent ) const {
	    WriteKMLObject< T >::write( out , data_ , indent , name_ ); }
        WriteableConcept* copy( void ) const {
            return new WriteableModel( data_ , name_ );
        }

	T data_;
        std::string name_;
    };

    std::unique_ptr< WriteableConcept > object_;
};



// static_assert( std::is_default_constructible< KMLEntity > , "" );



} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_ENTITY_H_INCLUDED
