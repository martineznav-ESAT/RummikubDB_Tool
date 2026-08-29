// @author Jonathan Martínez Navarro

#ifndef DataBaseManager_H
#define DataBaseManager_H

#include <esat_extra/sqlite3.h>
#include "../Libs/CustomLibs/TList.h"
#include "./ScreenModules/ModulesManager.h"

namespace DataBaseManager{
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

    enum PopUpType{
        POP_INFO,
        POP_ERROR,
        TOTAL_POPUPTYPES
    };

    struct PopUpValues{
        char* name = nullptr;
        bool is_opening = false;
        PopUpType popup_type = PopUpType::POP_INFO;
        char* popup_msg = nullptr;
    };

    extern sqlite3 *db;
    extern PopUpValues notif_pop_up;

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
    int QueryErrorManager(int qResult);

    //Applies the param values to the PopUpValues struct given and opens the modal if said so
    void SetPopUpValues(PopUpValues *pop_up, PopUpType nt_type, char* msg, bool open = true);

    //Draws the given pop_up based on its values
    void DrawPopUp(PopUpValues *pop_up);

    //Given a query string, returns the type of query it is based on the first word of the query
    QueryType GetQueryType(char* query);

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif