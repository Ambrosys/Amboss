/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */

#ifndef AMBOSS_KML_WRITEABLE_H_INCLUDED
#define AMBOSS_KML_WRITEABLE_H_INCLUDED

#include <ostream>
#include <memory>
#include <type_traits>

namespace Amboss {
namespace KML {



template< class T >
struct WriteObject ;



template< class T >
inline void writeObject( std::ostream &out , const T &t , size_t indent )
{
    WriteObject< T >::write( out , t , indent );
}


class Writeable
{
public:

    Writeable( void ) : object_( nullptr ) { }

    template< class T >
    Writeable( T t ) : object_( new WriteableModel< T >( t ) ) { }

    Writeable( const Writeable &e ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }

    ~Writeable( void ) { }

    const Writeable& operator=( const Writeable &e ) {
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
	WriteableModel( T t ) : data_( t ) { }
	~WriteableModel( void ) { }
	void write( std::ostream &out , size_t indent ) const {
	    WriteObject< T >::write( out , data_ , indent ); }
        WriteableConcept* copy( void ) const {
            return new WriteableModel( data_ );
        }

	T data_;
    };

    std::unique_ptr< WriteableConcept > object_;
};



// static_assert( std::is_default_constructible< Writeable > , "" );



} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_WRITEABLE_H_INCLUDED
