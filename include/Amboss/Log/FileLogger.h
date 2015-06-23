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
    typedef typename BasicOStreamLogger< ThreadingModelT >::Formatter Formatter;
    typedef typename BasicOStreamLogger< ThreadingModelT >::Filter Filter;
    typedef typename BasicOStreamLogger< ThreadingModelT >::DefaultFormatter DefaultFormatter;
    typedef typename BasicOStreamLogger< ThreadingModelT >::DefaultFilter DefaultFilter;
    
    BasicFileLogger( std::string const &filename ,
                     Formatter formatter = DefaultFormatter() ,
                     Filter filter = DefaultFilter(),
                     std::ios_base::openmode mode = std::ios_base::out )
    : BaseType( formatter , filter ) , out_( std::make_shared< std::ofstream >( filename, mode ) )
    {
        this->setStream( * ( out_.get() ) );
    }
    
    bool good( void ) const
    {
        typename BaseType::GetStreamLock lock( this->getThreadingModel() );
        return out_->good();
    }

    void close( void )
    {
        out_->close();
        out_->clear();
    }

    void open( std::string const &filename, std::ios_base::openmode mode )
    {
        out_->open( filename, mode );
    }

private:
    
    std::shared_ptr< std::ofstream > out_;
};

typedef BasicFileLogger< SingleThreadModel > FileLogger;
typedef BasicFileLogger< MultiThreadModel > FileLoggerMT;


} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOG_FILELOGGER_H_INCLUDED
