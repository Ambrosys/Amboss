/*
 * LogEntryStream.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LOGENTRYSTREAM_H_INCLUDED
#define AMBOSS_LOGENTRYSTREAM_H_INCLUDED

#include <Amboss/Log/ILogger.h>
#include <Amboss/Log/LogEntry.h>
#include <Amboss/Log/GlobalLogger.h>


namespace Amboss {
namespace Log {


namespace Detail 
{

    class LogStreamWrapper
    {
    public:
 
        LogStreamWrapper( ILogger &logger , const LogEntry &entry )
            : isSet_( false ) , stream_() , logger_( logger ) , entry_( entry ) 
        {
        }

        ~LogStreamWrapper( void )
        {
            entry_.message = stream_.str();
            logger_.write( entry_ );
        }

        std::ostringstream& getStream( void ) { return stream_; }

        bool first( void ) { bool cur = isSet_; isSet_ = true ; return cur; } 

    private:

        bool isSet_;
        std::ostringstream stream_;
        ILogger &logger_;
        LogEntry entry_;
    };

} // namespace Detail


} // namespace Log
} // namespace Amboss




#define AMB_LOG_LEVEL( logger , logLevel )        \
    for( \
        Amboss::Log::Detail::LogStreamWrapper stream(                \
            logger ,                                                    \
            makeLogEntry( logLevel , "" , __FILE__ , __LINE__ ) ) ;     \
        !stream.first() ;                                               \
        )                                                               \
        stream.getStream()

#define AMB_LOG( logger ) AMB_LOG_LEVEL( logger , Amboss::Log::INFO )



#define AMB_GLOBAL_LOG_LEVEL( logLevel ) AMB_LOG_LEVEL( Amboss::Log::GlobalLogger::getInstance() , logLevel )

#define AMB_GLOBAL_LOG AMB_GLOBAL_LOG_LEVEL( Amboss::Log::INFO )





#endif // AMBOSS_LOGENTRYSTREAM_H_INCLUDED
