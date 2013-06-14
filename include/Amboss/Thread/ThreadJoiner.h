/*
 * ThreadJoiner.h
 * Date: 2013-06-14
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_THREADJOINER_H_INCLUDED
#define AMBOSS_THREADJOINER_H_INCLUDED

#include <vector>
#include <thread>


namespace Amboss {
namespace Thread {


class ThreadJoiner
{
public:

    typedef std::vector< std::thread > ThreadContainer;

    explicit ThreadJoiner( ThreadContainer& threads )
        : threads_( threads )
    { }
    
    ~ThreadJoiner( void )
    {
        for( auto &thread : threads_ )
        {
            if( thread.joinable() ) thread.join();
        }
    }

private:

    ThreadContainer& threads_;
};



} // namespace Thread
} // namespace Amboss


#endif // AMBOSS_THREADJOINER_H_INCLUDED
