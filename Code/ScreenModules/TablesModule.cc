// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>
#include <esat_extra/sqlite3.h>

#include "./ModulesManager.h"
#include "../DataBaseManager.h"
#include "../Callbacks.h"

#include "../../Libs/CustomLibs/Utils.h"
#include "../../Libs/CustomLibs/TList.h"

namespace TablesModule{
    //TablesModule Globals

    //List that contains dynamically all the table names in the database
    TList::ListNode* db_tables;

    int qResult = 0;

    int selectedTable = -1; //Unselected by default

    //Inicialization function
    void Init(){
        db_tables = TList::CreateList();

        qResult = sqlite3_exec(DataBaseManager::db, DataBaseManager::GetBaseQuery(DataBaseManager::BaseSQL_Querys::GET_TABLES), Callbacks::CB_GetTables, &db_tables, &(DataBaseManager::error_msg));   
        DataBaseManager::QueryErrorManager(qResult, DataBaseManager::error_msg);
    }


    //Function that executes the basic select query for the table selected at the moment
    void CallSelectedTableQuery(){
        char* st_query = DataBaseManager::GetBaseQuery(DataBaseManager::BaseSQL_Querys::SELECT_QUERY, TList::GetIndexListNode(db_tables, selectedTable)->info.str_info);

        qResult = DataBaseManager::ExecuteSelectQuery(st_query);

        free(st_query);
    }

    //Shows the available tables as interactive selectables
    void ShowAvailableTables(){

        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,ImVec2(0.0f, 0.5f));

        for (int i = 0; i < TList::ListLength(db_tables); i++){
            //Creates the selectable widget as well as checking if it's the one currently selected
            if (
                ImGui::Selectable(
                    TList::GetIndexListNode(db_tables, i)->info.str_info, 
                    selectedTable == i, 
                    0,
                    ImVec2(0, 25)
                )
            ){
                ContentModule::content_info.is_loaded = false;
                //If there's a selected table at the moment of the list creation or on table selection, a basic Select query is called
                //for the selected table, showing the information in the ContentModule
                // printf("Selected %s\n", TList::GetIndexListNode(db_tables, i)->info.str_info);
                selectedTable = i;
                
                CallSelectedTableQuery();
            }
        }

        ImGui::PopStyleVar();
    }

    //Draws on screen the left column that portraits the available tables of the database
    void Draw(){
        //Window Init
        ImGui::Begin("Rummikub DB", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*1.0f});
        ImGui::SetWindowPos({0.0f, 0.0f});

        ShowAvailableTables();

        ImGui::End();
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        TList::ClearList(&db_tables);
    }
}
