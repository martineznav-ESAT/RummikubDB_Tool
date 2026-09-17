// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>
#include <stdlib.h>

#include "./ContentModule.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace ContentModule{
    #define NOT_PROCESSING -1
    //QueryContent Globals
    ContentInfo content_info;
    
    //Inicialization function
    void Init(){
        content_info.is_loaded = false;
        content_info.num_columns = 0;
        content_info.num_rows = 0;
        content_info.values = TList::CreateList();
        content_info.insert_row = NOT_PROCESSING;
        content_info.update_row = NOT_PROCESSING;
    }

    void OnAddButton(){
        TList::ListInfo info_aux;
        TList::ListNode* row_aux;
        TList::ListInfo row_info_aux;

        // printf("ON CLICK ADD BUTTON\n");
        row_aux = TList::CreateList();

        for (int i = content_info.num_columns-1; i >= 0 ; i--){
            //Row Data
            info_aux.celldata_info.db_value = (char*) malloc(DataBaseManager::GetTableColData(i).buff_size);
            info_aux.celldata_info.update_value = (char*) malloc(DataBaseManager::GetTableColData(i).buff_size);

            //Load Row Data
            strcpy(info_aux.celldata_info.db_value , "\0");
            strcpy(info_aux.celldata_info.update_value , "\0");

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
            &content_info.values, 
            TList::ListType::LIST,
            row_info_aux
        );

        content_info.num_rows = TList::ListLength(content_info.values);
        //The new inserted row will always be the head of the list, index 0. Yet the row id should be the corresponding to the previous length 
        content_info.insert_row = 0;
    }

    void OnDeleteButton(int r){
        char* d_query = nullptr;

        d_query = DataBaseManager::GetBaseQuery(
            DataBaseManager::BaseSQL_Querys::BASIC_DELETE,
            TList::GetIndexListNode(TablesModule::db_tables, TablesModule::selectedTable)->info.str_info,
            TList::GetLastListNode(content_info.values)->info.list_info->info.coldata_info.name, 
            TList::GetIndexListNode(
                TList::GetIndexListNode(content_info.values, r)->info.list_info, 
                0                                                                
            )->info.str_info
        );

        //DEBUG
        printf(
            "DELETE QUERY:\n %s\n",
            d_query
        );
        

        //DELETE REGISTER VALUE ASSOCIATED WITH THE BUTTON ROW AND UPDATE THE SELECTED TABLE 
        DataBaseManager::ExecuteDeleteQuery(d_query);

        free(d_query);
    }

    void OnInsertButton(int r){
        char* i_query = nullptr;
        char cols_s[512] = "\0";
        char values_s[512] = "\0";
        char aux_str[254] = "\0";
        TList::ListNode* row_node = TList::GetIndexListNode(content_info.values, r)->info.list_info;
        TList::ListNode* cell_aux = nullptr;
        char* aux_type = nullptr;

        //DEBUG
        // printf("OnInsertButton ROW %d\n",r);
        // TList::PrintList(row_node);

        for (int i = ContentModule::content_info.num_columns-1; i >= 0; i--){
            cell_aux = TList::GetIndexListNode(row_node, i);

            //Checks if there's a value available to insert for the current cell
            if(
                cell_aux != nullptr && 
                cell_aux->info.celldata_info.update_value != nullptr && 
                strcmp(cell_aux->info.celldata_info.update_value, "\0") != 0
            ){
                if(strcmp(cols_s, "\0") == 0){
                    //Save col name
                    strcpy(cols_s, DataBaseManager::GetTableColData(i).name);

                    //Save value based on type
                    Utils::GetStringWordAtPosition(&aux_type, DataBaseManager::GetTableColData(i).type, 0);
                    if(strcmp(aux_type, "VARCHAR") == 0 || strcmp(aux_type, "CHAR") == 0){
                        sprintf(aux_str, "'%s'", cell_aux->info.celldata_info.update_value);
                        strcpy(values_s, aux_str);
                    }else{
                        strcpy(values_s, cell_aux->info.celldata_info.update_value);
                    }
                }else{
                    //Concat col name
                    sprintf(aux_str, ", %s", DataBaseManager::GetTableColData(i).name);
                    strcat(cols_s, aux_str);

                    //Concat value based on type
                    Utils::GetStringWordAtPosition(&aux_type, DataBaseManager::GetTableColData(i).type, 0);
                    if(strcmp(aux_type, "VARCHAR") == 0 || strcmp(aux_type, "CHAR") == 0){
                        sprintf(aux_str, ", '%s'", cell_aux->info.celldata_info.update_value);
                        strcat(values_s, aux_str);
                    }else{
                        sprintf(aux_str, ", %s", cell_aux->info.celldata_info.update_value);
                        strcat(values_s, cell_aux->info.celldata_info.update_value);
                    }
                }
            }
        }

        //DEBUG
        // printf("COLS TO INSERT INTO -> %s\n",cols_s);
        // printf("VALUES TO INSERT -> %s\n",values_s);
        

        i_query = DataBaseManager::GetBaseQuery(
            DataBaseManager::BaseSQL_Querys::BASIC_INSERT,
            TList::GetIndexListNode(TablesModule::db_tables, TablesModule::selectedTable)->info.str_info,
            nullptr, 
            cols_s,
            values_s
        );

        //DEBUG
        // printf(
        //     "INSERT QUERY:\n %s\n",
        //     i_query
        // );
        

        //INSERTS REGISTER VALUE OF THE ACTUAL PROCESSING INSERT ROW AND UPDATE THE SELECTED TABLE 
        DataBaseManager::ExecuteInsertQuery(i_query);

        if(i_query != nullptr){
            free(i_query);
        }
    }

    void DrawCellInputValue(int row, int col){
        TList::ListNode* cell = 
            TList::GetIndexListNode(
                TList::GetIndexListNode(content_info.values, row)->info.list_info, 
                col                                                                
            );
        TList::ColumnData col_metadata = DataBaseManager::GetTableColData(col);

        char cell_label[100];
        sprintf(cell_label, "##cell_%d_%d", row, col);

        ImGui::SetNextItemWidth(-FLT_MIN);
        
        ImGui::InputText(
            cell_label,
            cell->info.celldata_info.update_value,
            col_metadata.buff_size,
            DataBaseManager::GetInputFlagsByType(col_metadata.type)
        );
    }

    //Draws the table of the current query content. No matter if it is a custom query or a table selection
    void DrawContentTable(){

        if(content_info.is_loaded && !TList::IsEmptyList(&(content_info.values))){
            
            if(content_info.insert_row == NOT_PROCESSING){
                if(ImGui::Button("ADD NEW ROW", ImVec2(-1,0))){
                    OnAddButton();
                }
            }else{
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 100, 100, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 100, 100, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(100, 100, 100, 255));
                ImGui::Button("ADDING ROW...", ImVec2(-1,0));
                ImGui::PopStyleColor(3);
            }

            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));

            ImGui::BeginTable(
                "content", content_info.num_columns+1, 
                ImGuiTableFlags_Borders | 
                ImGuiTableFlags_RowBg | 
                ImGuiTableFlags_Resizable | 
                ImGuiTableFlags_ScrollX | 
                ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_ColumnsWidthStretch
            );

            //DEBUG
            // printf("\nSTART DRAW CONTENT TABLE\n");
            // TList::PrintList(content_info.values);
            for (int r = content_info.num_rows-1; r >= 0; r--){
                //DEBUG
                // printf("PRINTING ROW %d\n",r);
                // TList::PrintList(TList::GetIndexListNode(content_info.values, r)->info.list_info);

                if(r == content_info.num_rows-1){
                    //Draws Header value
                    for (int c = 0; c < content_info.num_columns; c++){
                        ImGui::TableSetupColumn(
                            TList::GetIndexListNode(
                                TList::GetIndexListNode(content_info.values, r)->info.list_info, //Row
                                c                                                                //Col
                            )->info.coldata_info.name
                        );
                    }
                    ImGui::TableSetupColumn(
                        "",
                        ImGuiTableColumnFlags_WidthFixed |
                        ImGuiTableColumnFlags_NoResize,
                        75.f
                    );
                    ImGui::TableHeadersRow();
                }else{
                    //Draws Register value
                    ImGui::TableNextRow();
                    for (int c = 0; c < content_info.num_columns; c++){
                        ImGui::TableNextColumn();
                        DrawCellInputValue(r,c);
                    }
                    ImGui::TableNextColumn();

                    if(r != content_info.insert_row && r != content_info.update_row){
                        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(180, 60, 60, 255));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(200, 70, 70, 255));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(160, 50, 50, 255));
                        if(ImGui::Button("X", ImVec2(-FLT_MIN,0))){
                            OnDeleteButton(r);
                        }
                        ImGui::PopStyleColor(3);
                    }else{
                        if(r == content_info.insert_row){
                            ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(80, 180, 100, 255));
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 200, 120, 255));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(60, 160, 80, 255));
                            if(ImGui::Button("+", ImVec2(-FLT_MIN,0))){
                                OnInsertButton(r);
                            }
                            ImGui::PopStyleColor(3);
                        }
                    }
                    
                }
            }

            //DEBUG
            // printf("END DRAW CONTENT TABLE\n");
            
            
            ImGui::EndTable();

            ImGui::PopStyleVar();
        }
    }

    //Draws on the screen top space the result of the custom query or the content of the selected table
    void Draw(){
        ImGui::Begin("Query Content", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.671f, Utils::kWindowHeight*0.65f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.33f, 0.0f});

        DrawContentTable();

        ImGui::End();
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        TList::ClearList(&(content_info.values));
    }
}
