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
        "SELECT * from %s order by 1"
    };

    sqlite3 *db;
    char* error_msg = nullptr;

    //Given a query string, returns the type of query it is based on the first word of the query
    QueryType GetQueryType(char* query){
        QueryType result = QueryType::ERROR;

        if(query == nullptr || strlen(query) <= 0){
            printf("ERROR: Query is empty\n");
        }else{
            char* query_type = (char*) malloc(sizeof(char) * strlen(query)+1);

            strcpy(query_type, query);
            query_type = strtok(query_type, " ");

            printf("QUERY TYPE: %s\n", query_type);
            if(strcmp(strupr(query_type), "SELECT") == 0){
                result = QueryType::SELECT;
            }else if(strcmp(strupr(query_type), "UPDATE") == 0){
                result = QueryType::UPDATE;
            }else if(strcmp(strupr(query_type), "INSERT") == 0){
                result = QueryType::INSERT;
            }else if(strcmp(strupr(query_type), "DELETE") == 0){
                result = QueryType::DELETE;
            }

            free(query_type);
        }
        
        return result;
    }

    //Returns the SQL String corresponding to the parameter enum value 
    char* GetBaseQuery(BaseSQL_Querys query, char* tablename){
        char* r_query = nullptr; 

        switch (query){
        case BaseSQL_Querys::SELECT_QUERY:
            
            r_query = (char*) malloc(sizeof(char)*(1 + strlen(tablename) + strlen(kBaseSQL_Querys[(int)query])));

            snprintf(
                (char*)r_query,
                1 + strlen(kBaseSQL_Querys[(int)query]) + strlen(tablename),
                kBaseSQL_Querys[(int)query],
                tablename
            );

            break;
        
        default:
            r_query = kBaseSQL_Querys[(int)query];
            break;
        }

        //DEBUG
        // printf("%s\n\n",r_query);
        return r_query;
    }

     void GetColumnsOnEmptyQuery(char* st_query){
        printf("EMPTY QUERY\n");
        TList::ListInfo info_aux;
        
        sqlite3_stmt* stmt;

        sqlite3_prepare_v2(
            DataBaseManager::db,
            st_query,
            -1,
            &stmt,
            nullptr
        );

        ContentModule::content_info.is_loaded = true;
        ContentModule::content_info.num_columns = sqlite3_column_count(stmt);
        ContentModule::content_info.num_rows = 0;

        TList::ClearList(&(ContentModule::content_info.column_names));
        TList::ClearList(&(ContentModule::content_info.values));
        for (int i = 0; i < ContentModule::content_info.num_columns; i++) {

            info_aux.str_info = (char*)malloc(sizeof(char) * (strlen(sqlite3_column_name(stmt, i))+1));
            strcpy(info_aux.str_info, sqlite3_column_name(stmt, i));
            TList::InsertList(&(ContentModule::content_info.column_names), TList::ListType::STRING ,info_aux);

            //DEBUG
            // printf("%s\n", info_aux.str_info);
        }

        sqlite3_finalize(stmt);
    }

    //Executes the given SELECT query and returns the result of the query execution
    int ExecuteSelectQuery(char* s_query, bool is_custom_query){
        int qResult = 1;
        Callbacks::is_callback_called = false;
        qResult = sqlite3_exec(DataBaseManager::db, s_query, Callbacks::CB_SelectQuery, &(ContentModule::content_info), &(DataBaseManager::error_msg));   
        if(!Callbacks::is_callback_called && !is_custom_query){
            GetColumnsOnEmptyQuery(s_query);
        }
        return qResult;
    }

    //Executes the given SELECT query and returns the result of the query execution
    int ExecuteUpdateQuery(char* u_query, bool is_custom_query){
        int qResult = 1;
        TList::ListInfo aux_info;
        aux_info.str_info = nullptr;

        Utils::GetStringWordAtPosition(&aux_info.str_info, u_query, 1);

        //DEBUG
        printf("TABLE NAME: %s\n", aux_info.str_info);
        

        if(aux_info.str_info == nullptr || TList::FindInList(TablesModule::db_tables, aux_info) == nullptr ){
            printf("ERROR: Table not found in database\n");
            DataBaseManager::error_msg = (char*) malloc(sizeof(char) * (strlen("Table not found in database")+1));  
            strcpy(DataBaseManager::error_msg, "Table not found in database");
            qResult = SQLITE_ERROR;
        }else{
            qResult = sqlite3_exec(DataBaseManager::db, u_query, nullptr, nullptr, &(DataBaseManager::error_msg));   
        }

        free(aux_info.str_info);

        return qResult;
    }

    //Query error management
    int QueryErrorManager(int qResult, char** e_msg){
        if(qResult != SQLITE_OK){
            fprintf(stderr, "SQL Error:\n%s\n",*e_msg);
            sqlite3_free(*e_msg);
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
