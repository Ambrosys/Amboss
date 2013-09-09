/*
 * Amboss/Util/Version.h
 * Date: 2013-09-09
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_UTIL_VERSION_H_INCLUDED
#define AMBOSS_UTIL_VERSION_H_INCLUDED

#include <Amboss/AmbossVersion.h>
#include <string>

namespace Amboss {

inline std::string getVersionString( void )
{
    return std::string( "v" ) + std::to_string( AMBOSS_VERSION_MAJOR ) + "." + std::to_string( AMBOSS_VERSION_MINOR ) + "." + std::to_string( AMBOSS_VERSION_PATCH );
}

constexpr int getVersionMajor( void )
{
    return AMBOSS_VERSION_MAJOR;
}

constexpr int getVersionMinor( void )
{
    return AMBOSS_VERSION_MINOR;
}

constexpr int getVersionPatch( void )
{
    return AMBOSS_VERSION_PATCH;
}

inline std::string getVersionSha1( void )
{
    return AMBOSS_VERSION_SHA1;
};


} // namespace Amboss


#endif // AMBOSS_UTIL_VERSION_H_INCLUDED
