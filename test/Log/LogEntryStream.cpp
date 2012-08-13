/*
 * LogEntryStream.cpp
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <sstream>

#include <Amboss/Log/LogEntryStream.h>

#include <gtest/gtest.h>

using namespace std;
using namespace Amboss::Log;

class LogEntryStreamTest : public ::testing::Test {
 protected:

    void SetUp( void )
    {
        formatter_ = []( const LogEntry &e ) {
            std::string s = std::string( "[" ) + logLevelName( e.logLevel ) + std::string( "]" );
            return s + std::string( " : " ) + e.message + "\n";
        };
    }

    ostringstream stream_;
    std::function< std::string( const LogEntry & ) > formatter_;
};

TEST_F( LogEntryStreamTest , testAmbLog )
{
    OStreamLogger logger( stream_ , formatter_ );
    AMB_LOG( logger ) << "message3";
    EXPECT_EQ( stream_.str() , "[Info] : message3\n" );
}

TEST_F( LogEntryStreamTest , testAmbLogLevel )
{
    OStreamLogger logger( stream_ , formatter_ );
    AMB_LOG_LEVEL( logger , WARNING ) << "message4";
    EXPECT_EQ( stream_.str() , "[Warning] : message4\n" );
}

TEST_F( LogEntryStreamTest , testAmbLogGlobal )
{
    LoggerCollection &logger = GlobalLogger::getInstance();
    logger.data().clear();
    logger.data().push_back( std::shared_ptr< ILogger >( new OStreamLogger( stream_ ,  formatter_ ) ) );
    AMB_GLOBAL_LOG << "message1";
    EXPECT_EQ( stream_.str() , "[Info] : message1\n" );
}

TEST_F( LogEntryStreamTest , testAmbLogLevelGlobal )
{
    LoggerCollection &logger = GlobalLogger::getInstance();
    logger.data().clear();
    logger.data().push_back( std::shared_ptr< ILogger >( new OStreamLogger( stream_ ,  formatter_ ) ) );
    AMB_GLOBAL_LOG_LEVEL( DEBUG ) << "message2";
    EXPECT_EQ( stream_.str() , "[Debug] : message2\n" );
}
