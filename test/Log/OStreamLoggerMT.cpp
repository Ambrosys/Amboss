/*
 * OStreamLoggerMT.cpp
 * Date: 2013-05-28
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <Amboss/Log/OStreamLogger.h>

#include <gtest/gtest.h>

#include <sstream>
#include <thread>


using namespace std;
using namespace Amboss::Log;

void thread_func( OStreamLoggerMT &logger )
{
    std::this_thread::sleep_for( std::chrono::microseconds( 500 ) );
    logger.write( makeLogEntry( INFO , "message1" , "filename" , 23 ) );
}

TEST( OStreamLoggerMT , test1 )
{
    ostringstream stream;
    OStreamLoggerMT logger( stream );
    logger.setFormatter( OStreamLogger::Formatter( []( const LogEntry &e ) {
        std::string s = std::string( "[" ) + logLevelName( e.logLevel ) + std::string( "]" );
        return s + std::string( " : " ) + e.message + "\n";
    } ) );
    std::thread t( thread_func , std::ref( logger ) );
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    logger.write( makeLogEntry( INFO , "message2" , "filename" , 23 ) );

    t.join();

    EXPECT_EQ( stream.str() , "[Info] : message1\n[Info] : message2\n" );
}
