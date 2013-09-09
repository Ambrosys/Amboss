/*
 * test/Util/Version.cpp
 * Date: 2013-09-09
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <Amboss/Util/Version.h>

#include <gtest/gtest.h>

#define TESTNAME Version

using namespace std;

TEST( TESTNAME , TestVersionString )
{
    std::string v = Amboss::getVersionString();
}

TEST( TESTNAME , TestVersionMajor )
{
    int major = Amboss::getVersionMajor();
}

TEST( TESTNAME , TestVersionMinor )
{    
    int minor = Amboss::getVersionMinor();
}

TEST( TESTNAME , TestVersionPatch )
{    
    int patch = Amboss::getVersionPatch();
}

TEST( TESTNAME , TestVersionSha1 )
{    
    std::string sha1 = Amboss::getVersionSha1();
}
