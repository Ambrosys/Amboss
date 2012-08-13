/*
 * GlobalLogger.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_GLOBALLOGGER_H_INCLUDED
#define AMBOSS_GLOBALLOGGER_H_INCLUDED

#include <Amboss/Log/LoggerCollection.h>


namespace Amboss {
namespace Log {

class GlobalLogger
{
public:

    static LoggerCollection& getInstance( void )
    {
        static LoggerCollection instance;
        return instance;
    }

private:

    GlobalLogger( void );
    GlobalLogger( const GlobalLogger& );
    GlobalLogger& operator=( const GlobalLogger& );

};




} // namespace Log
} // namespace Amboss


#endif // AMBOSS_GLOBALLOGGER_H_INCLUDED
