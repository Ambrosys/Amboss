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

#include <stdexcept>

#include "sqlite3.h"


namespace Amboss {
namespace Sqlite3 {


    class Sqlite3DB
    {
    public:

        Sqlite3DB( const std::string &filename )
            : database_( 0 ) , filename_( filename ) , good_( true )
        {
            init();
        }

        ~Sqlite3DB( void )
        {
            if( good_ )
                sqlite3_close( database_ );
        }

        void query( const std::string &queryStr , std::vector< std::vector< std::string > > &results )
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
                throw std::runtime_error( std::string( "Query error from query : " ) + queryStr + " : " +  error );
        }

        std::vector< std::vector< std::string > > query( const std::string &queryStr )
        {
            std::vector< std::vector< std::string > > results;
            query( queryStr , results );
            return results; 
        }

        bool good( void ) const { return good_; }

        explicit operator bool() { return good_; }


    private:

        void init( void )
        {
            if( sqlite3_open( filename_.c_str() , &database_ ) != SQLITE_OK )
            {
                good_ = false;
                std::cerr << "Konnte Sqlite Datenbank " << filename_ << " nicht oeffnen!" << std::endl;
            }
        }

        sqlite3* database_;
        std::string filename_;
        bool good_;
    };




} // namespace Sqlite3
} // namespace Amboss


#endif // AMBOSS_SQLITE3DB_H_INCLUDED
