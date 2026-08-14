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
    char* kBaseSQL_Querys[] = {
        "SELECT name FROM sqlite_master WHERE type = 'table' and name != 'sqlite_sequence'",
        "SELECT * from %s"
    };

    sqlite3 *db;
    char* error_msg = 0;

    //Returns the SQL String corresponding to the parameter enum value 
    char* GetBaseQuery(BaseSQL_Querys query, char* tablename){
        char* r_query = nullptr; 

        switch (query){
        case BaseSQL_Querys::SELECT_TABLENAME:
            
            r_query = (char*) malloc(sizeof(char)*(strlen(tablename) + strlen(kBaseSQL_Querys[(int)query])));

            snprintf(
                (char*)r_query,
                strlen(kBaseSQL_Querys[(int)query]) + strlen(tablename),
                kBaseSQL_Querys[(int)query],
                tablename
            );

            break;
        
        default:
            r_query = kBaseSQL_Querys[(int)query];
            break;
        }

        printf("%s\n\n",r_query);
        return r_query;
    }

    //Query error management
    int QueryErrorManager(int qResult, char* e_msg){
        if(qResult != SQLITE_OK){
            fprintf(stderr, "Failed to select data\n");
            fprintf(stderr, "SQL Error: %s\n",e_msg);

            sqlite3_free(e_msg);
        }

        return qResult;
    }

    //Inicialization function
    int Init(){
        int qResult = sqlite3_open(kDB_location, &db);

        if(qResult != SQLITE_OK){
            fprintf(stderr, "Could not open database: %s\n",sqlite3_errmsg(db));
            sqlite3_close(db);
        }else{
            TablesModule::Init();
            ContentModule::Init();
            CustomQueryModule::Init();
        }

        return qResult;
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        sqlite3_close(db);
        TablesModule::EmptyMemory();
        ContentModule::EmptyMemory();
        CustomQueryModule::EmptyMemory();
    }
}
