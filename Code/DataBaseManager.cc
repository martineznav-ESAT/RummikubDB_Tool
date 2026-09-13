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
        "SELECT * from %s order by 1",
        "pragma table_info(%s)",
        "delete from %s where %s = %s"
    };

    sqlite3 *db;
    PopUpValues notif_pop_up;

    //Given a query string, returns the type of query it is based on the first word of the query
    QueryType GetQueryType(char* query){
        QueryType result = QueryType::ERROR;

        if(query == nullptr || strlen(query) <= 0){
            DataBaseManager::SetPopUpValues(
                &DataBaseManager::notif_pop_up,
                DataBaseManager::PopUpType::POP_ERROR, 
                "Query is empty\n",
                true
            );
        }else{
            char* query_type = (char*) malloc(sizeof(char) * strlen(query)+1);

            strcpy(query_type, query);
            query_type = strtok(query_type, " ");

            //DEBUG
            // printf("QUERY TYPE: %s\n", query_type);
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
    char* GetBaseQuery(BaseSQL_Querys query, char* tablename, char* field, char* value){
        char* r_query = nullptr; 
        int query_length;

        switch (query){
            case BaseSQL_Querys::SELECT_QUERY:
                query_length = sizeof(char)*(1 + strlen(tablename) + strlen(kBaseSQL_Querys[(int)query]));
                
                r_query = (char*) malloc(query_length);

                //Builds the select query with the tablename given
                snprintf(
                    (char*)r_query,
                    query_length,
                    kBaseSQL_Querys[(int)query],
                    tablename
                );

                break;

            case BaseSQL_Querys::BASIC_DELETE:
                // printf("%s | %s | %s \n",tablename,field,value);

                query_length = sizeof(char)*(1 + strlen(tablename) + strlen(field) + strlen(value) + strlen(kBaseSQL_Querys[(int)query]));
                
                r_query = (char*) malloc(query_length);

                //Builds the select query with the tablename given
                snprintf(
                    (char*)r_query,
                    query_length,
                    kBaseSQL_Querys[(int)query],
                    tablename,
                    field,
                    value
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

    
    //Executes the given SELECT query and returns the result of the query execution
    int ExecuteSelectQuery(char* s_query, bool is_custom_query){
        int qResult = 1;
        sqlite3_stmt* stmt;
        TList::ListInfo info_aux;
        TList::ListNode* row_aux;
        TList::ListInfo row_info_aux;


        qResult = sqlite3_prepare_v2(
            DataBaseManager::db,
            s_query,
            -1,
            &stmt,
            nullptr
        );

        // printf("ExecuteSelectQuery -> sqlite3_prepare_v2 -> %d\n",qResult);

        if(qResult == SQLITE_OK){
            ContentModule::content_info.num_columns = sqlite3_column_count(stmt);
            ContentModule::content_info.update_row = NOT_PROCESSING;
            ContentModule::content_info.insert_row = NOT_PROCESSING;
            TList::ClearList(&(ContentModule::content_info.values));
            ContentModule::content_info.is_loaded = false;
            if(!ContentModule::content_info.is_loaded){
                row_aux = TList::CreateList();

                // printf("ExecuteSelectQuery -> columns -> %d\n",sqlite3_column_count(stmt));
                for (int i = ContentModule::content_info.num_columns-1; i >= 0; i--){
                    strcpy(info_aux.coldata_info.name, sqlite3_column_name(stmt,i));
                    strcpy(info_aux.coldata_info.type, sqlite3_column_decltype(stmt,i));

                    TList::InsertList(
                        &row_aux, 
                        TList::ListType::COLUMNDATA,
                        info_aux
                    );
                }

                //Save column values row
                row_info_aux.list_info = row_aux;
                TList::InsertList(
                    &(ContentModule::content_info.values), 
                    TList::ListType::LIST,
                    row_info_aux
                );
                ContentModule::content_info.is_loaded = true;
            }

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                row_aux = TList::CreateList();


                for (int i = ContentModule::content_info.num_columns-1; i >= 0 ; i--){
                    //Row Data
                    if(sqlite3_column_text(stmt,i) == nullptr){
                        info_aux.celldata_info.db_value = (char*) malloc(sizeof(char) * (strlen("\0")+1));
                        info_aux.celldata_info.update_value = (char*) malloc(sizeof(char) * (strlen("\0")+1));

                        strcpy(info_aux.celldata_info.db_value , "\0");
                        strcpy(info_aux.celldata_info.update_value , "\0");
                    }else{
                        info_aux.celldata_info.db_value = (char*) malloc(sizeof(char) * (strlen((char*)sqlite3_column_text(stmt,i))+1));
                        info_aux.celldata_info.update_value = (char*) malloc(sizeof(char) * (strlen((char*)sqlite3_column_text(stmt,i))+1));
                        
                        strcpy(info_aux.celldata_info.db_value , (char*)sqlite3_column_text(stmt,i));
                        strcpy(info_aux.celldata_info.update_value , (char*)sqlite3_column_text(stmt,i));
                    }

                    info_aux.celldata_info.col = i;
                    info_aux.celldata_info.row = TList::ListLength(ContentModule::content_info.values);
                    
                    //Save N register in table given as parameter
                    TList::InsertList(
                        &row_aux, 
                        TList::ListType::CELLDATA,
                        info_aux
                    );
                }

                //Save register values row
                row_info_aux.list_info = row_aux;
                TList::InsertList(
                    &(ContentModule::content_info.values), 
                    TList::ListType::LIST,
                    row_info_aux
                );
            }

            ContentModule::content_info.num_rows = TList::ListLength(ContentModule::content_info.values);
        }


        sqlite3_finalize(stmt);

        // TList::PrintList(ContentModule::content_info.values);

        return qResult;
    }

    //Sets the popup values to show an error saying the table has not been found
    void SetTableNotFoundError(){
        DataBaseManager::SetPopUpValues(
            &DataBaseManager::notif_pop_up,
            DataBaseManager::PopUpType::POP_ERROR, 
            "Table not found in database\n"
        );
    }

    //Executes the given Update query and shows the result of the query execution
    int ExecuteUpdateQuery(char* u_query, bool is_custom_query){
        int qResult = 1;
        TList::ListInfo aux_info;
        aux_info.str_info = nullptr;

        Utils::GetStringWordAtPosition(&aux_info.str_info, u_query, 1);
        strupr(aux_info.str_info);

        //DEBUG
        // printf("TABLE NAME: %s\n", aux_info.str_info);
        

        if(aux_info.str_info == nullptr || TList::FindInList(TablesModule::db_tables, aux_info) == nullptr ){
            SetTableNotFoundError();
            qResult = SQLITE_ERROR;
        }else{
            qResult = sqlite3_exec(DataBaseManager::db, u_query, nullptr, nullptr, &(DataBaseManager::notif_pop_up.popup_msg));   
        }

        free(aux_info.str_info);

        return qResult;
    }

    //Executes the given Insert query and returns the result of the query execution
    int ExecuteInsertQuery(char* i_query, bool is_custom_query){
        int qResult = 1;
        TList::ListInfo aux_info;
        aux_info.str_info = nullptr;

        Utils::GetStringWordAtPosition(&aux_info.str_info, i_query, 2);
        strupr(aux_info.str_info);

        //DEBUG
        // printf("TABLE NAME: %s\n", aux_info.str_info);
        

        if(aux_info.str_info == nullptr || TList::FindInList(TablesModule::db_tables, aux_info) == nullptr ){
            SetTableNotFoundError();
            qResult = SQLITE_ERROR;
        }else{
            qResult = sqlite3_exec(DataBaseManager::db, i_query, nullptr, nullptr, &(DataBaseManager::notif_pop_up.popup_msg));   
        }

        free(aux_info.str_info);

        return qResult;
    }

    //Executes the given Delete query and returns the result of the query execution
    int ExecuteDeleteQuery(char* d_query, bool is_custom_query){
        int qResult = 1;
        TList::ListInfo aux_info;
        aux_info.str_info = nullptr;


        Utils::GetStringWordAtPosition(&aux_info.str_info, d_query, 2);
        if(aux_info.str_info){
            strupr(aux_info.str_info);
        }

        //DEBUG
        // printf("TABLE NAME: %s\n", aux_info.str_info);
        

        if(aux_info.str_info == nullptr || TList::FindInList(TablesModule::db_tables, aux_info) == nullptr ){
            SetTableNotFoundError();
            qResult = SQLITE_ERROR;
        }else{
            qResult = sqlite3_exec(DataBaseManager::db, d_query, nullptr, nullptr, &(DataBaseManager::notif_pop_up.popup_msg));   
        }

        free(aux_info.str_info);

        return qResult;
    }

    //Query error management
    int QueryErrorManager(int qResult){

        if(qResult != SQLITE_OK){
            SetPopUpValues(
                &DataBaseManager::notif_pop_up,
                PopUpType::POP_ERROR,
                DataBaseManager::notif_pop_up.popup_msg
            );
        }

        return qResult;
    }

    //Applies the param values to the PopUpValues struct given and opens the pop up if it's currently closed
    void SetPopUpValues(PopUpValues *pop_up, PopUpType pop_type, char* msg, bool open){
        pop_up->popup_type = pop_type;

        //This conditionals are used with the objective of using custom messages and sqlite3 messages with the same popup_msg variable
        //Since sqlite3 frees the error message buffer or they can be the same location, the conditionals bypass this problem
        //and makes sure the popup message shows without crashing

        if(pop_up->popup_msg == nullptr){
            pop_up->popup_msg = (char*) malloc(sizeof(char)*254);
        }
        if(pop_up->popup_msg != msg){
            strcpy(pop_up->popup_msg, msg);
        }
        pop_up->is_opening = open;
    }

    //Draws the given pop_up based on its values
    void DrawPopUp(PopUpValues *pop_up){
        float popup_width = 400;
        char popup_label[256];
        ImVec2 center = ImVec2(
            ImGui::GetIO().DisplaySize.x * 0.5f,
            ImGui::GetIO().DisplaySize.y * 0.5f
        );
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        
        //Popup label selection based on POP_TYPE
        switch (pop_up->popup_type){
            case DataBaseManager::PopUpType::POP_ERROR:
                snprintf(popup_label, sizeof(popup_label), "ERROR ON QUERY STATEMENT##%s",pop_up->name);
            break;

            case DataBaseManager::PopUpType::POP_INFO:
                snprintf(popup_label, sizeof(popup_label), "QUERY INFO##%s",pop_up->name);
            break;
        }

        if(pop_up->is_opening){
            ImGui::OpenPopup(popup_label);
            pop_up->is_opening = false;
        }

        ImGui::SetNextWindowSize(
            ImVec2(popup_width, 0),
            ImGuiCond_Appearing
        );

        if (ImGui::BeginPopupModal(popup_label, NULL, ImGuiWindowFlags_NoResize)){
            ImGui::TextWrapped("%s", pop_up->popup_msg);

            ImGui::Separator();

            if (ImGui::Button("OK", ImVec2(-1, 0))){
                ImGui::CloseCurrentPopup(); 
            }
            ImGui::EndPopup();
        }
    }

    //Inicialization function
    int Init(){
        int qResult = sqlite3_open(kDB_location, &db);
        
        notif_pop_up.name = "Notification_PopUp";
        notif_pop_up.popup_msg = (char*) malloc(sizeof(char)*254);


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
        free(notif_pop_up.popup_msg);
    }
}
