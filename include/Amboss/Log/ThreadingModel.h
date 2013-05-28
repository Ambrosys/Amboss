/*
 * ThreadingModel.h
 * Date: 2013-05-28
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_THREADINGMODEL_H_INCLUDED
#define AMBOSS_THREADINGMODEL_H_INCLUDED

#include <mutex>


namespace Amboss {
namespace Log {


struct SingleThreadModel
{
    void lock( void ) const { }
    void unlock( void ) const { }
    bool try_lock( void ) const { return true; }
};

class MultiThreadModel
{
public:

    MultiThreadModel( void ) : mutex_() {}
    MultiThreadModel( MultiThreadModel const& ) : mutex_() {}
    MultiThreadModel& operator=( MultiThreadModel const& ) { return *this; }
    
    void lock( void ) const { mutex_.lock(); }
    void unlock( void ) const { mutex_.unlock(); }
    bool try_lock( void ) const { return mutex_.try_lock(); }

private:

    mutable std::mutex mutex_;
};



} // namespace Log
} // namespace Amboss


#endif // AMBOSS_THREADINGMODEL_H_INCLUDED
