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
#include <Amboss/Log/ThreadingModel.h>

#include <memory>

namespace Amboss {
namespace Log {

    template< class ThreadingModelT >
    class BasicLoggerCollection : public ILogger
    {
    public:

        typedef std::vector< std::shared_ptr< ILogger > > LoggerSequence;
        typedef ThreadingModelT ThreadingModel;

        // TODO : Optimize and find the correct lock types;
        typedef std::lock_guard< ThreadingModel > WriteLock;
        typedef std::lock_guard< ThreadingModel > RemoveAllLoggerLock;
        typedef std::lock_guard< ThreadingModel > AddLoggerLock;

        BasicLoggerCollection( void ) : data_()
        {
            data_.push_back( std::make_shared< OStreamLogger >() );
        }

        void write( const LogEntry &e )
        {
            WriteLock lock( threadingModel_ );
            for( size_t i=0 ; i<data_.size() ; ++i ) data_[i]->write( e );
        }

        void addLogger( std::shared_ptr< ILogger > logger )
        {
            AddLoggerLock lock( threadingModel_ );
            data_.push_back( logger );
        }

        void removeAllLoggers( void )
        {
            RemoveAllLoggerLock lock( threadingModel_ );
            data_.clear();
        }

    private:

        LoggerSequence data_;
        ThreadingModel threadingModel_;
    };

    typedef BasicLoggerCollection< SingleThreadModel > LoggerCollection;
    typedef BasicLoggerCollection< MultiThreadModel > LoggerCollectionMT;




} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOGGERCOLLECTION_H_INCLUDED
