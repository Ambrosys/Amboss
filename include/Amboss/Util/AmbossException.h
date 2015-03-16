/*
 * Amboss/Util/AmbossException.h
 * Date: 2015-03-16
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_UTIL_AMBOSSEXCEPTION_H_INCLUDED
#define AMBOSS_UTIL_AMBOSSEXCEPTION_H_INCLUDED

#include <exception>
#include <string>


namespace Amboss {
namespace Util {

class AmbossException : public std::exception
{
    
public:
    
    explicit AmbossException( std::string const &msg )
    :   msg_( std::string( "AmbossException: " ) + msg )
    {
    }
    
    virtual ~AmbossException() throw()
    {
    }
    
    virtual const char *what() const throw()
    {
        return msg_.c_str();
    }
    
private:
    
    std::string msg_;
};


} // namespace Util
} // namespace Amboss


#endif // AMBOSS_UTIL_AMBOSSEXCEPTION_H_INCLUDED
