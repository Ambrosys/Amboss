/*
 * Amboss/Log/FileLogger.h
 * Date: 2013-11-28
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LOG_FILELOGGER_H_INCLUDED
#define AMBOSS_LOG_FILELOGGER_H_INCLUDED

#include <Amboss/Log/OStreamLogger.h>
#include <memory>
#include <fstream>

namespace Amboss {
namespace Log {

template< typename ThreadingModelT >
class BasicFileLogger : public BasicOStreamLogger< ThreadingModelT >
{
    typedef BasicOStreamLogger< ThreadingModelT > BaseType;
    
public:
    
    
    BasicFileLogger( std::string const &filename ,
                    Formatter formatter = BaseType::DefaultFormatter() ,
                    Filter filter = BaseType::DefaultFilter() )
    : BaseType( formatter , filter ) , out_( std::make_shared< std::ofstream >( filename ) )
    {
        this->setStream( * ( out_.get() ) );
    }
    
    bool good( void ) const
    {
        return out_->good();
    }
    
    std::shared_ptr< std::ofstream > out_;
};

typedef BasicFileLogger< SingleThreadModel > FileLogger;
typedef BasicFileLogger< MultiThreadModel > FileLoggerMT;




} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOG_FILELOGGER_H_INCLUDED
