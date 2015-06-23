/*
 * ILogger.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_ILOGGER_H_INCLUDED
#define AMBOSS_ILOGGER_H_INCLUDED


namespace Amboss {
namespace Log {

    class LogEntry;

    class ILogger
    {
    public:

        virtual ~ILogger() {}
        virtual void write( const LogEntry &l ) = 0;
    };



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_ILOGGER_H_INCLUDED
