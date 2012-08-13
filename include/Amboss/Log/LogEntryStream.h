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


namespace Amboss {
namespace Log {


namespace Detail 
{

    class LogStreamWrapper
    {
    public:
 
        LogStreamWrapper( LogEntryLogger &logger , const LogEntry &entry )
            : isSet_( false ) , stream_() , logger_( logger ) , entry_( entry ) 
        {
        }

        ~LogStreamWrapper( void )
        {
            entry_.message = stream_.str();
            logger_.writeLogEntry( entry_ );
        }

        std::ostringstream& getStream( void ) { return stream_; }

        bool first( void ) { bool cur = isSet_; isSet_ = true ; return cur; } 

    private:

        bool isSet_;
        std::ostringstream stream_;
        LogEntryLogger &logger_;
        LogEntry entry_;
    };

} // namespace Detail


} // namespace Log
} // namespace Amboss




#define ST_LOG_LEVEL( logger , logLevel )        \
    for( \
        SuperToll::Common::Logging::Detail::LogStreamWrapper stream( \
                       logger ,                                      \
                       makeLogEntry( logLevel , "" , __FILE__ , __LINE__ ) ) ; \
    !stream.first() ;                                                   \
        )                                                               \
        stream.getStream()

#define ST_LOG( logger ) ST_LOG_LEVEL( logger , SuperToll::Common::Logging::INFO )



#define ST_GLOBAL_LOG_LEVEL( logLevel ) ST_LOG_LEVEL( SuperToll::Common::Logging::GlobalLogger::getInstance() , logLevel )

#define ST_GLOBAL_LOG ST_GLOBAL_LOG_LEVEL( SuperToll::Common::Logging::INFO )



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOGENTRYSTREAM_H_INCLUDED
