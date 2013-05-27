/*
 * LoggerCollection.cpp
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <gtest/gtest.h>

#include <Amboss/Log/LoggerCollection.h>

using namespace std;
using namespace Amboss::Log;

TEST( LoggerCollection , test1 )
{
    LoggerCollection logger;
    logger.removeAllLoggers();
    ostringstream stream;
    auto formatter = []( const LogEntry &e ) {
        std::string s = std::string( "[" ) + logLevelName( e.logLevel ) + std::string( "]" );
        return s + std::string( " : " ) + e.message + "\n";
    };
    auto filter1 = []( const LogEntry &e ) {
        return e.logLevel == DEBUG;
    };
    auto filter2 = []( const LogEntry &e ) {
        return e.logLevel == INFO;
    };

    ostringstream stream1 , stream2 ;
    logger.addLogger( std::make_shared< OStreamLogger >( stream1 , formatter , filter1 ) );
    logger.addLogger( std::make_shared< OStreamLogger >( stream2 , formatter , filter2 ) );
    logger.write( makeLogEntry( DEBUG , "message1" ) );
    logger.write( makeLogEntry( INFO , "message2" ) );

    EXPECT_EQ( stream1.str() , "[Debug] : message1\n" );
    EXPECT_EQ( stream2.str() , "[Info] : message2\n" );
}
