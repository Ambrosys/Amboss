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
struct WriteObject ;



template< class T >
inline void writeObject( std::ostream &out , const T &t , size_t indent , const std::string &name )
{
    WriteObject< T >::write( out , t , indent , name );
}


class Entity
{
public:

    Entity( void ) : object_( nullptr ) { }

    template< class T >
    Entity( T t , const std::string &name = std::string( "" ) ) : object_( new WriteableModel< T >( t , name ) ) { }

    Entity( const Entity &e ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }

    Entity( const Entity &e , const std::string &name ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }

    ~Entity( void ) { }

    const Entity& operator=( const Entity &e ) {
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
	    WriteObject< T >::write( out , data_ , indent , name_ ); }
        WriteableConcept* copy( void ) const {
            return new WriteableModel( data_ , name_ );
        }

	T data_;
        std::string name_;
    };

    std::unique_ptr< WriteableConcept > object_;
};



// static_assert( std::is_default_constructible< Entity > , "" );



} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_ENTITY_H_INCLUDED
