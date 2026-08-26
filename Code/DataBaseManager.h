// @author Jonathan Martínez Navarro

#ifndef DataBaseManager_H
#define DataBaseManager_H

#include <esat_extra/sqlite3.h>
#include "../Libs/CustomLibs/TList.h"
#include "./ScreenModules/ModulesManager.h"

namespace DataBaseManager{
    extern sqlite3 *db;
    extern char* error_msg;

    enum BaseSQL_Querys{
        GET_TABLES,
        SELECT_QUERY,
        TOTAL_QUERYS
    };

    enum QueryType{
        SELECT,
        UPDATE,
        INSERT,
        DELETE,
        ERROR,
        TOTAL_QUERYTYPES
    };

    //Inicialization function
    int Init();

    //Returns the SQL String corresponding to the parameter enum value 
    char* GetBaseQuery(BaseSQL_Querys query, char* tablename = nullptr);

    //Executes a select query given 
    int ExecuteSelectQuery(char* s_query, bool is_custom_query = false);

    //Executes an update query given 
    int ExecuteUpdateQuery(char* u_query, bool is_custom_query = false);

    //Executes an insert query given 
    int ExecuteInsertQuery(char* i_query, bool is_custom_query = false);

    //Executes an delete query given 
    int ExecuteDeleteQuery(char* d_query, bool is_custom_query = false);

    //Query error management
    int QueryErrorManager(int qResult, char** e_msg);

    //Given a query string, returns the type of query it is based on the first word of the query
    QueryType GetQueryType(char* query);

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif