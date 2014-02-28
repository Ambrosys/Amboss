/*
 * Amboss/Log/NullLogger.h
 * Date: 2014-02-28
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LOG_NULLLOGGER_H_INCLUDED
#define AMBOSS_LOG_NULLLOGGER_H_INCLUDED


namespace Amboss {
namespace Log {


class NullLogger
{
public:

    NullLogger( void );
    ~NullLogger( void );
};



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOG_NULLLOGGER_H_INCLUDED
