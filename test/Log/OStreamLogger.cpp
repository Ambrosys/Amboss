/*
 * OStreamLogger.cpp
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

#include <Amboss/Log/OStreamLogger.h>

using namespace std;
using namespace Amboss::Log;

TEST( OStreamLogger , test1 )
{
    ostringstream stream;
    OStreamLogger logger( stream );
    logger.setFormatter( OStreamLogger::Formatter( []( const LogEntry &e ) {
        std::string s = std::string( "[" ) + logLevelName( e.logLevel ) + std::string( "]" );
        return s + std::string( " : " ) + e.message + "\n";
    } ) );
    logger.write( makeLogEntry( INFO , "message" , "filename" , 23 ) );

    EXPECT_EQ( stream.str() , "[Info] : message\n" );


}
