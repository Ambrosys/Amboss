/*
 * Timer.h
 * Date: 2013-04-06
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef AMBOSS_TIMER_H_INCLUDED
#define AMBOSS_TIMER_H_INCLUDED

#include <chrono>


namespace Amboss {
namespace Util {


class Timer
{
    typedef std::chrono::high_resolution_clock clock_type;
    clock_type::time_point m_start_time;

    template< class T >
    static inline double get_seconds( T t )
    {
        return double( std::chrono::duration_cast< std::chrono::microseconds >( t ).count() ) * 1.0e-6;
    }

    template< class T >
    static inline double get_milliseconds( T t )
    {
        return double( std::chrono::duration_cast< std::chrono::milliseconds >( t ).count() );
    }
/*
    static inline double get_microseconds( T t )
    {
        return double( std::chrono::duration_cast< std::chrono::microseconds >( t ).count() );
    }
*/
public:

    Timer( void ) : m_start_time( clock_type::now() ) { }

    inline double seconds( void ) const
    {
        return get_seconds( clock_type::now() - m_start_time );
    }

    inline double milliseconds( void ) const
    {
        return get_milliseconds(clock_type::now() - m_start_time );
    }

/*    inline double microseconds( void ) const
    {
        return get_microseconds(clock_type::now() - m_start_time );
    }
  */  
    inline void restart( void )
    {
        m_start_time = clock_type::now();
    }
};


} // namespace Util
} // namespace Amboss


#endif // AMBOSS_TIMER_H_INCLUDED
