/*
 * Feature.h
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_FEATURE_H_INCLUDED
#define AMBOSS_FEATURE_H_INCLUDED

#include <memory>

namespace Amboss {
namespace KML {


template< class T >
struct WriteFeature ;



template< class T >
inline void writeFeature( std::ostream &out , const T &t , size_t indent )
{
    WriteFeature< T >::write( out , t , indent );
}


class Feature
{
public:

    Feature( void ) : object_( nullptr ) { }

    template< class T >
    Feature( T t ) : object_( new FeatureModel< T >( t ) ) { }

    Feature( const Feature &e ) : object_( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) { }

    ~Feature( void ) { }

    const Feature& operator=( const Feature &e ) {
        object_.reset( ( e.object_ != nullptr ) ? e.object_->copy() : nullptr ) ;
        return *this;
    }

    void write( std::ostream &out , size_t indent ) const {
        object_->write( out , indent );
    }

private:

    struct FeatureConcept
    {
	virtual ~FeatureConcept( void ) { };
	virtual void write( std::ostream &out , size_t indent ) const = 0;
        virtual FeatureConcept* copy( void ) const = 0;
    };

    template< class T >
    struct FeatureModel : public FeatureConcept
    {
	FeatureModel( T t ) : data_( t ) { }
	~FeatureModel( void ) { }
	void write( std::ostream &out , size_t indent ) const {
	    WriteFeature< T >::write( out , data_ , indent ); }
        FeatureConcept* copy( void ) const {
            return new FeatureModel( data_ );
        }

	T data_;
    };

    std::unique_ptr< FeatureConcept > object_;
};




} // namespace KML
} // namespace Amboss


#endif // AMBOSS_FEATURE_H_INCLUDED
