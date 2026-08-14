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
        SELECT_TABLENAME,
        TOTAL_QUERYS
    };

    //Inicialization function
    int Init();

    //Returns the SQL String corresponding to the parameter enum value 
    char* GetBaseQuery(BaseSQL_Querys query, char* tablename = nullptr);

    //Query error management
    int QueryErrorManager(int qResult, char* e_msg);

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif