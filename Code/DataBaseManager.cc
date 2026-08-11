// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>
#include <esat_extra/sqlite3.h>

#include "./DataBaseManager.h"
#include "./Callbacks.h"

#include "../Libs/CustomLibs/Utils.h"
#include "../Libs/CustomLibs/TList.h"

namespace DataBaseManager{
    //Constant value that represents the sqlite database file location
    const char* kDB_location = "./Assets/DDBB/Rummikub_DB.db";

    //Constant values of all the base/default sql querys used in the tool
    const char* kBaseSQL_Querys[] = {
        "SELECT name FROM sqlite_master WHERE type = 'table' and name != 'sqlite_sequence'"
    };

    //List that contains dynamically all the table names in the database
    TList::ListNode* db_tables;

    sqlite3 *db;
    char* error_msg = 0;

    //Returns the SQL String corresponding to the parameter enum value 
    const char* GetBaseQuery(BaseSQL_Querys query){
        return kBaseSQL_Querys[(int)query];
    }

    //Inicialization function
    void Init(){
        db_tables = TList::CreateList();
        int qResult = sqlite3_open(kDB_location, &db);

        if(qResult != SQLITE_OK){
            fprintf(stderr, "Could not open database: %s\n",sqlite3_errmsg(db));
            sqlite3_close(db);
        }else{

            qResult = sqlite3_exec(db, GetBaseQuery(BaseSQL_Querys::GET_TABLES), Callbacks::CB_GetTables, &db_tables, &error_msg);   
            if(qResult != SQLITE_OK){
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL Error: %s\n",error_msg);

                sqlite3_free(error_msg);
            }
        }
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        sqlite3_close(db);
        TList::ClearList(&db_tables);
    }
}
