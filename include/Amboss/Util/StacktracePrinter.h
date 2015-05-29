/*
 * StacktracePrinter.h
 * Date: 2013-06-18
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_STACKTRACEPRINTER_H_INCLUDED
#define AMBOSS_STACKTRACEPRINTER_H_INCLUDED

#include <execinfo.h>
#include <csignal>
#include <cstdlib>
#include <ostream>


namespace Amboss {
namespace Util {


inline std::ostream& printStacktraceSimple( std::ostream &out )
{
    void *array[50];
    size_t size = backtrace ( array , 50 );
    char **messages = backtrace_symbols( array , size );
    // print out all the frames to stderr
    bool first = true;
    for( size_t i = 0 ; i <size && messages != NULL ; ++i )
    {
        if( first ) first = false;
        else out << '\n';
        out << "[BT] : (" << i << ") " << messages[i];
    }
    out << std::flush;
    free( messages );
    return out;
}

struct StacktraceSimple
{
    inline std::ostream& operator()( std::ostream &out ) const
    {
        return printStacktraceSimple( out );
    }
};

inline std::ostream& operator<<( std::ostream &out , StacktraceSimple const& s )
{
    return s( out );
}


    
} // namespace Util
} // namespace Amboss


#endif // AMBOSS_STACKTRACEPRINTER_H_INCLUDED
