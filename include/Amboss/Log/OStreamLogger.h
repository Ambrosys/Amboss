/*
 * OStreamLogger.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_OSTREAMLOGGER_H_INCLUDED
#define AMBOSS_OSTREAMLOGGER_H_INCLUDED

#include <Amboss/Log/ILogger.h>
#include <Amboss/Log/LogEntry.h>

#include <functional>
#include <string>
#include <ostream>
#include <sstream>


namespace Amboss {
namespace Log {


    class OStreamLogger : public ILogger
    {
    public:

        typedef std::function< std::string( const LogEntry& ) > Formatter;
        typedef std::function< bool( const LogEntry& ) > Filter;

        struct DefaultFilter {
            inline bool operator()( const LogEntry &l ) const {
                return true;
            }
        };

        struct DefaultFormatter {
            inline std::string operator()( const LogEntry &e ) const {
                std::ostringstream timeStr;
                timeStr << e.time;

                std::string s = std::string( "[" ) + logLevelName( e.logLevel ) + std::string( "]" );
                s += std::string( " [" ) + timeStr.str() + std::string( "]" );
                return s + std::string( " : " ) + e.message + "\n";
            }
        };



        OStreamLogger( std::ostream &stream = std::cout ,
                       Formatter formatter = DefaultFormatter() ,
                       Filter filter = DefaultFilter() )
            : stream_( &stream ) , formatter_( formatter ) , filter_( filter ) { }

        const Formatter& formatter( void ) const { return formatter_; }
        Formatter& formatter( void ) { return formatter_; }

        const Filter& filter( void ) const { return filter_; }
        Filter& filter( void ) { return filter_; }

        std::ostream& stream( void ) { return *stream_; }
        void setStream( std::ostream &out ) { stream_ = &out; }

        void write( const LogEntry &l )
        {
            if( ( stream_ != 0 ) && bool( formatter_ ) && bool( filter_ ) )
            {
                if( filter_( l ) ) 
                {
                    (*stream_) << formatter_( l );
                }
            }
        }

    
    private:

        std::ostream* stream_;
        Formatter formatter_;
        Filter filter_;
    };


} // namespace Log
} // namespace Amboss


#endif // AMBOSS_OSTREAMLOGGER_H_INCLUDED
