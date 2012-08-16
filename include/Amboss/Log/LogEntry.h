/*
 * LogEntry.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LOGENTRY_H_INCLUDED
#define AMBOSS_LOGENTRY_H_INCLUDED

#include <string>
#include <utility>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Amboss {
namespace Log {

    enum LogLevel
    {
        NOISE ,
        PROGRESS ,
        INFO ,
        DEBUG ,
        WARNING ,
        ERROR ,
        ASSERT 
    };

    inline std::string logLevelName( LogLevel l )
    {
        switch( l )
        {
        case NOISE : return "Noise"; break;
        case PROGRESS : return "Progress"; break;
        case INFO : return "Info"; break;
        case DEBUG : return "Debug"; break;
        case WARNING : return "Warning"; break;
        case ERROR : return "Error"; break;
        case ASSERT : return "Assert"; break;
        };
        return "";
    }

    inline LogLevel stringToLogLevel( const std::string &str )
    {
        if( str == "Noise" ) return NOISE;
        else if( str == "Progress" ) return PROGRESS;
        else if( str == "Info" ) return INFO;
        else if( str == "Debug" ) return DEBUG;
        else if( str == "Warning" ) return WARNING;
        else if( str == "Error" ) return ERROR;
        else if( str == "Assert" ) return ASSERT;
        else throw std::runtime_error( std::string( "Unknow log level type " ) + str );
    }

    struct LogEntry
    {
        typedef std::pair< std::string , std::string > AttributeType;
        typedef std::vector< AttributeType > AttributeSequence;
        typedef boost::posix_time::ptime TimeType;

        TimeType time;
        LogLevel logLevel ;
        std::string message;
        std::string filename;
        int lineNumber;
        AttributeSequence attributes;
    };

    inline LogEntry makeLogEntry(
        LogLevel logLevel ,
        const std::string &message ,
        const std::string &filename = "" ,
        int lineNumber = 0 ,
        const LogEntry::AttributeSequence &attributes = LogEntry::AttributeSequence()
        )
    {
        LogEntry l;
        l.time = LogEntry::TimeType( boost::posix_time::second_clock::local_time() );
        l.logLevel = logLevel;
        l.message = message;
        l.filename = filename;
        l.lineNumber = lineNumber;
        l.attributes = attributes;
        return l;
    }



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOGENTRY_H_INCLUDED
