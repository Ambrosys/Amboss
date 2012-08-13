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


namespace Amboss {
namespace Log {



class LogEntryLogger 
{
public:

    typedef std::vector< LogStream > StreamSequence;

    LogEntryLogger( void )
        : streams_( 1 , LogStream() )
    { }

    ~LogEntryLogger( void )
    { }

    void writeLogEntry( const LogEntry &e )
    {
        for( size_t i=0 ; i<streams_.size() ; ++i ) streams_[i].write( e );
    }

    StreamSequence& streams( void ) { return streams_; }
    const StreamSequence& streams( void ) const { return streams_; }

private:

    StreamSequence streams_;
};


} // namespace Log
} // namespace Amboss


#endif // AMBOSS_LOGGERCOLLECTION_H_INCLUDED
