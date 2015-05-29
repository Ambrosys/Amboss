/*
 * Sqlite3DB.h
 * Date: 2012-07-31
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 * Copyright: Karsten Ahnert
 *
 * Use, modification and distribution is subject to the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */



#ifndef AMBOSS_SQLITE3DB_H_INCLUDED
#define AMBOSS_SQLITE3DB_H_INCLUDED

#include <Amboss/Util/AmbossException.h>

#include <stdexcept>

#include "sqlite3.h"


namespace Amboss {
namespace Sqlite3 {


    class Sqlite3DB
    {
    public:

        typedef std::vector< std::vector< std::string > > ResultType;

        Sqlite3DB( void )
            : database_( 0 ) , filename_() 
        {
        }

        Sqlite3DB( const std::string &filename )
            : database_( 0 ) , filename_( filename )
        {
            open( filename );
        }

        ~Sqlite3DB( void )
        {
            close();
        }

        void open( const std::string &filename )
        {
            close();
            if( sqlite3_open( filename.c_str() , &database_ ) != SQLITE_OK )
            {
                throw Amboss::Util::AmbossException( std::string( "Could not open Sqlite DB " ) + filename + "." );
            }
            filename_ = filename;
        }

        void close( void )
        {
            filename_ = "";
            if( database_ != 0 ) sqlite3_close( database_ );
        }

        void query( const std::string &queryStr , ResultType &results )
        {
            sqlite3_stmt *statement;
            if( sqlite3_prepare_v2( database_ , queryStr.c_str() , -1 , &statement , 0 ) == SQLITE_OK )
            {
                int cols = sqlite3_column_count( statement );
                int result = 0;
                while( true )
                {
                    result = sqlite3_step( statement );
	             
                    if( result == SQLITE_ROW )
                    {
                        std::vector< std::string > values;
                        for(int col = 0; col < cols; col++)
                        {
                            values.push_back( ( char* ) sqlite3_column_text(statement, col) );
                        }
                        results.push_back(values);
                    }
                    else
                    {
                        break;  
                    }
                }
        
                sqlite3_finalize(statement);
            }
	     
            std::string error = sqlite3_errmsg( database_ );
            if(error != "not an error")
                throw Amboss::Util::AmbossException( std::string( "Query error from query : " ) + queryStr + " : " +  error );
        }

        ResultType query( const std::string &queryStr )
        {
            std::vector< std::vector< std::string > > results;
            query( queryStr , results );
            return results; 
        }

    private:

        sqlite3* database_;
        std::string filename_;
    };




} // namespace Sqlite3
} // namespace Amboss


#endif // AMBOSS_SQLITE3DB_H_INCLUDED
