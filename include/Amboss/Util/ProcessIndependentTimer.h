/*
 * Amboss/Util/ProcessIndependentTimer.h
 * Date: 2014-03-03
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_UTIL_PROCESSINDEPENDENTTIMER_H_INCLUDED
#define AMBOSS_UTIL_PROCESSINDEPENDENTTIMER_H_INCLUDED


#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace Amboss {
namespace Util {


class ProcessIndependentTimer
{
    using clock_type = boost::posix_time::microsec_clock;
    using time_type = boost::posix_time::ptime;
    
public:

    ProcessIndependentTimer( void ) : m_start_time( clock_type::local_time() ) { }
    
    inline double seconds( void ) const
    {
        return get_seconds( boost::posix_time::time_duration( clock_type::local_time() - m_start_time ) );
    }

    inline void restart( void )
    {
        m_start_time = clock_type::local_time();
    }
    
private:
    
    template< typename T >
    inline double get_seconds( T t )  const
    {
        return ( t.total_microseconds() / 1000000.0 );
    }
    
    boost::posix_time::ptime m_start_time;

};



} // namespace Util
} // namespace Amboss


#endif // AMBOSS_UTIL_PROCESSINDENPENDENTTIMER_H_INCLUDED
