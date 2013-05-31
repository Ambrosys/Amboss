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
#include <Amboss/Log/ThreadingModel.h>

#include <functional>
#include <string>
#include <ostream>
#include <sstream>


namespace Amboss {
namespace Log {

    template< class ThreadingModelT >
    class BasicOStreamLogger : public ILogger
    {
    public:

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


        typedef ThreadingModelT ThreadingModel;
        typedef std::function< std::string( const LogEntry& ) > Formatter;
        typedef std::function< bool( const LogEntry& ) > Filter;

        // TODO : Optimize and find the correct lock types;
        typedef std::lock_guard< ThreadingModel > GetFormatterLock;
        typedef std::lock_guard< ThreadingModel > SetFormatterLock;
        typedef std::lock_guard< ThreadingModel > GetFilterLock;
        typedef std::lock_guard< ThreadingModel > SetFilterLock;
        typedef std::lock_guard< ThreadingModel > GetStreamLock;
        typedef std::lock_guard< ThreadingModel > SetStreamLock;
        typedef std::lock_guard< ThreadingModel > WriteLock;



        BasicOStreamLogger( std::ostream &stream = std::cout , Formatter formatter = DefaultFormatter() , Filter filter = DefaultFilter() )
        : stream_( &stream ) , formatter_( std::move( formatter ) ) , filter_( std::move( filter ) ) , threadingModel_()
        {
        }

        Formatter getFormatter( void ) const
        {
            GetFormatterLock lock( threadingModel_ );
            return formatter_;
        }

        void setFormatter( Formatter formatter )
        {
            SetFormatterLock lock( threadingModel_ );
            formatter_ = formatter; 
        }

        Filter getFilter( void ) const
        {
            GetFilterLock lock( threadingModel_ );
            return filter_;
        }

        void setFilter( Filter filter )
        {
            SetFilterLock lock( threadingModel_ );
            filter_ = filter;
        }

        std::ostream& getStream( void ) const
        {
            GetStreamLock lock( threadingModel_ );
            return *stream_;
        }

        void setStream( std::ostream &out )
        {
            SetStreamLock lock( threadingModel_ );
            stream_ = &out;
        }

        void write( const LogEntry &l )
        {
            WriteLock lock( threadingModel_ );
            writeUnlocked( l );
        }


    private:

        void writeUnlocked( const LogEntry &l )
        {
            if( ( stream_ != 0 ) && bool( formatter_ ) && bool( filter_ ) )
            {
                if( filter_( l ) )
                {
                    (*stream_) << formatter_( l );
                    (*stream_) << std::flush;
                }
            }
        }

        std::ostream *stream_;
        Formatter formatter_;
        Filter filter_;
        ThreadingModel threadingModel_;
    };

    typedef BasicOStreamLogger< SingleThreadModel > OStreamLogger;
    typedef BasicOStreamLogger< MultiThreadModel > OStreamLoggerMT;



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_OSTREAMLOGGER_H_INCLUDED
