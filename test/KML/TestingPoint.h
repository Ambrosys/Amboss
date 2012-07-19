/*
 * TestingPoint.h
 * Date: 2012-07-19
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_TEST_TESTINGPOINT_H_INCLUDED
#define AMBOSS_TEST_TESTINGPOINT_H_INCLUDED

#include <Amboss/KML/Writeable.h>
#include <Amboss/KML/WriterHelper.h>


struct TestingPoint
{
    TestingPoint( void ) : x( 0.0 ) , y( 0.0 ) { }
    TestingPoint( double _x , double _y ) : x( _x ) , y( _y ) { }
    double x;
    double y;
};


namespace Amboss {
namespace KML {

template<>
struct WriteObject< TestingPoint >
{
    static inline void write( std::ostream &out , const TestingPoint &p , size_t indent )
    {
	writePoint( out , p.x , p.y , indent );
    }
};

} // namespace KML
} // namespace Amboss 





#endif // AMBOSS_TEST_TESTINGPOINT_H_INCLUDED
