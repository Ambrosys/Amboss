/*
 * MultiGeometry.h
 * Date: 2012-08-24
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_MULTIGEOMETRY_H_INCLUDED
#define AMBOSS_MULTIGEOMETRY_H_INCLUDED

#include <Amboss/KML/Geometry.h>
#include <Amboss/KML/WriterHelper.h>

namespace Amboss {
namespace KML {


    class MultiGeometry
    {
    public:

        typedef std::vector< Geometry > SequenceType;

        template< class T >
        void add( T t )
        {
            data_.push_back( Geometry( t ) );
        }

        SequenceType& data( void ) { return data_; }
        const SequenceType& data( void ) const { return data_; }

    private:

        SequenceType data_;
    };

    template<>
    struct WriteGeometry< MultiGeometry >
    {
        static void write( std::ostream &out , const MultiGeometry &mg , size_t indent )
        {
            out <<  getIndent( indent + 0 ) << "<MultiGeometry>" << "\n";
            for( size_t i=0 ; i<mg.data().size() ; ++i )
                mg.data()[i].write( out , indent + 1 );
            out << getIndent( indent ) << "</MultiGeometry>" << "\n";
        }
    };

} // namespace KML
} // namespace Amboss


#endif // AMBOSS_MULTIGEOMETRY_H_INCLUDED
