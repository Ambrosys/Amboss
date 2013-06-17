/*
 * Exception.h
 * Date: 2013-06-17
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef AMBOSS_EXCEPTION_H_INCLUDED
#define AMBOSS_EXCEPTION_H_INCLUDED

#include <string>
#include <ostream>
#include <exception>


namespace Amboss {
namespace Util {

    inline std::string indent( size_t level )
    {
        std::string ret = "";
        for( size_t i=0 ; i<level ; ++i ) ret += "  ";
        return ret;
    }

    inline void printException( const std::exception& e , int level , std::ostream &out , bool first = true )
    {
        if( !first ) out << "\n";
        out << indent( level ) << "Exception : " << e.what();
        
        try
        {
            std::rethrow_if_nested( e );
        }
        catch( const std::exception& e )
        {
            printException( e , level + 1 , out , false );
        }
        catch( ... )
        {
        }
    }

    struct PrettyExceptionPrinter
    {
        std::exception const& e_;
        PrettyExceptionPrinter( std::exception const&e ) : e_( e ) { }
        
        inline std::ostream& operator()( std::ostream &out ) const
        {
            printException( e_ , 0 , out );
            return out;
        }
    };

    inline std::ostream& operator<<( std::ostream& out , PrettyExceptionPrinter const& p )
    {
        return p( out );
    }




} // namespace Util
} // namespace Amboss


#endif // AMBOSS_EXCEPTION_H_INCLUDED
