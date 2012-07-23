/*
 * Description
 *
 * @author Karsten Ahnert (karsten.ahnert@ambrosys.de)
 */

#ifndef AMBOSS_KML_GEOMETRY_H_INCLUDED
#define AMBOSS_KML_GEOMETRY_H_INCLUDED

#include <ostream>
#include <memory>
#include <type_traits>

namespace Amboss {
namespace KML {



template< class T >
struct WriteGeometry ;



template< class T >
inline void writeGeometry( std::ostream &out , const T &t , size_t indent )
{
    WriteGeometry< T >::write( out , t , indent );
}


class Geometry
{
public:

    Geometry( void ) : object_( nullptr ) { }

    template< class T >
    Geometry( T t ) : object_( new GeometryModel< T >( t ) ) { }

    Geometry( const Geometry &e ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }


    const Geometry& operator=( const Geometry &e ) {
        object_.reset( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) ;
        return *this;
    }

    void write( std::ostream &out , size_t indent ) const {
        object_->write( out , indent );
    }

private:

    struct GeometryConcept
    {
	virtual ~GeometryConcept( void ) { };
	virtual void write( std::ostream &out , size_t indent ) const = 0;
        virtual GeometryConcept* copy( void ) const = 0;
    };

    template< class T >
    struct GeometryModel : public GeometryConcept
    {
	GeometryModel( T t ) : data_( t ) { }
	~GeometryModel( void ) { }
	void write( std::ostream &out , size_t indent ) const {
	    WriteGeometry< T >::write( out , data_ , indent ); }
        GeometryConcept* copy( void ) const {
            return new GeometryModel( data_ );
        }

	T data_;
    };

    std::unique_ptr< GeometryConcept > object_;
};



// static_assert( std::is_default_constructible< Geometry > , "" );



} // namespace KML
} // namespace Amboss

#endif // AMBOSS_KML_GEOMETRY_H_INCLUDED
