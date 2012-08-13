/*
 * LoggerCollection.h
 * Date: 2012-08-13
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_LOGGERCOLLECTION_H_INCLUDED
#define AMBOSS_LOGGERCOLLECTION_H_INCLUDED

#include <Amboss/Log/ILogger.h>
#include <Amboss/Log/OStreamLogger.h>

#include <memory>

namespace Amboss {
namespace Log {


    // ToDo : Create Sequence of Loggers
    class LoggerCollection : public ILogger
    {
    public:

        typedef std::vector< std::shared_ptr< ILogger > > LoggerSequence;

        LoggerCollection( void )
            : data_()
        {
            data_.push_back( std::shared_ptr< ILogger >( new OStreamLogger() ) );
        }

        void write( const LogEntry &e )
        {
            for( size_t i=0 ; i<data_.size() ; ++i ) data_[i]->write( e );
        }

        LoggerSequence& data( void ) { return data_; }
        const LoggerSequence& data( void ) const { return data_; }

    private:

        LoggerSequence data_;
    };


} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOGGERCOLLECTION_H_INCLUDED
