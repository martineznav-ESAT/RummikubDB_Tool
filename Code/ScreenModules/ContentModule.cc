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
            info_aux.celldata_info.db_value = (char*) malloc(DataBaseManager::GetTableColData(i)->buff_size);
            info_aux.celldata_info.update_value = (char*) malloc(DataBaseManager::GetTableColData(i)->buff_size);

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
        char where_clause[512] = "\0";
        char aux_str[256] = "\0";
        char* aux_type = nullptr;
        bool is_first; //Loop Aux
        TList::ListNode* header_row = TList::GetLastListNode(content_info.values)->info.list_info;
        TList::ListNode* actual_register = TList::GetIndexListNode(content_info.values, r)->info.list_info;
        TList::ColumnData* actual_col = nullptr;

        // DEBUG
        // printf("ROW TO DELETE %d\n",r);
        // TList::PrintList(actual_register);

        for (int c = 0, is_first = true; c < content_info.num_columns; c++){
            actual_col = DataBaseManager::GetTableColData(c);
            if(actual_col->is_pk){
                Utils::GetStringWordAtPosition(&aux_type, actual_col->type, 0);
                if(is_first){
                    switch (DataBaseManager::StringToCellType(aux_type)){
                        case DataBaseManager::CellType::VARCHAR:
                        case DataBaseManager::CellType::CHAR:
                            sprintf(
                                aux_str,
                                "WHERE %s = '%s' ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                            break;
                        
                        default:
                            sprintf(
                                aux_str,
                                "WHERE %s = %s ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                        break;
                    }

                    is_first = false;
                }else{
                    switch (DataBaseManager::StringToCellType(aux_type)){
                        case DataBaseManager::CellType::VARCHAR:
                        case DataBaseManager::CellType::CHAR:
                            sprintf(
                                aux_str,
                                "AND %s = '%s' ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                            break;
                        
                        default:
                            sprintf(
                                aux_str,
                                "AND %s = %s ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                        break;
                    }
                }

                strcat(where_clause,aux_str);
            }
        }
        

        d_query = DataBaseManager::GetBaseQuery(
            DataBaseManager::BaseSQL_Querys::BASIC_DELETE,
            TList::GetIndexListNode(TablesModule::db_tables, TablesModule::selectedTable)->info.str_info,
            where_clause
        );

        //DEBUG
        // printf(
        //     "DELETE QUERY:\n %s\n",
        //     d_query
        // );
        

        //DELETE REGISTER VALUE ASSOCIATED WITH THE BUTTON ROW AND UPDATE THE SELECTED TABLE 
        DataBaseManager::ExecuteDeleteQuery(d_query);

        free(d_query);
    }

    void OnInsertButton(int r){
        char* i_query = nullptr;
        char cols_s[512] = "\0";
        char values_s[512] = "\0";
        char aux_str[256] = "\0";
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
                    strcpy(cols_s, DataBaseManager::GetTableColData(i)->name);

                    //Save value based on type
                    Utils::GetStringWordAtPosition(&aux_type, DataBaseManager::GetTableColData(i)->type, 0);
                    if(strcmp(aux_type, "VARCHAR") == 0 || strcmp(aux_type, "CHAR") == 0){
                        sprintf(aux_str, "'%s'", cell_aux->info.celldata_info.update_value);
                        strcpy(values_s, aux_str);
                    }else{
                        strcpy(values_s, cell_aux->info.celldata_info.update_value);
                    }
                }else{
                    //Concat col name
                    sprintf(aux_str, ", %s", DataBaseManager::GetTableColData(i)->name);
                    strcat(cols_s, aux_str);

                    //Concat value based on type
                    Utils::GetStringWordAtPosition(&aux_type, DataBaseManager::GetTableColData(i)->type, 0);
                    if(strcmp(aux_type, "VARCHAR") == 0 || strcmp(aux_type, "CHAR") == 0){
                        sprintf(aux_str, ", '%s'", cell_aux->info.celldata_info.update_value);
                        strcat(values_s, aux_str);
                    }else{
                        sprintf(aux_str, ", %s", cell_aux->info.celldata_info.update_value);
                        strcat(values_s, aux_str);
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

    void OnEditButton(int r){
        content_info.update_row = r;
    }

    void OnUpdateButton(int r){
        char* u_query = nullptr;
        char where_clause[512] = "\0";
        char aux_str[256] = "\0";
        char* aux_type = nullptr;
        bool is_first; //Loop aux
        TList::ListNode* header_row = TList::GetLastListNode(content_info.values)->info.list_info;
        TList::ListNode* actual_register = TList::GetIndexListNode(content_info.values, r)->info.list_info;
        TList::ColumnData* actual_col = nullptr;

        for (int c = 0, is_first = true; c < content_info.num_columns; c++){
            actual_col = DataBaseManager::GetTableColData(c);
            Utils::GetStringWordAtPosition(&aux_type, actual_col->type, 0);

            //Adds separation comma or not based on being the first column
            if(is_first){
                switch (DataBaseManager::StringToCellType(aux_type)){
                    case DataBaseManager::CellType::VARCHAR:
                    case DataBaseManager::CellType::CHAR:
                        sprintf(
                            aux_str,
                            "%s = '%s' ",
                            actual_col->name, 
                            TList::GetIndexListNode(actual_register,c)->info.celldata_info.update_value
                        );
                        break;
                    
                    default:
                        sprintf(
                            aux_str,
                            "%s = %s ",
                            actual_col->name, 
                            TList::GetIndexListNode(actual_register,c)->info.celldata_info.update_value
                        );
                    break;
                }

                is_first = false;
            }else{
                switch (DataBaseManager::StringToCellType(aux_type)){
                    case DataBaseManager::CellType::VARCHAR:
                    case DataBaseManager::CellType::CHAR:
                        sprintf(
                            aux_str,
                            ", %s = '%s' ",
                            actual_col->name, 
                            TList::GetIndexListNode(actual_register,c)->info.celldata_info.update_value
                        );
                        break;
                    
                    default:
                        sprintf(
                            aux_str,
                            ", %s = %s ",
                            actual_col->name, 
                            TList::GetIndexListNode(actual_register,c)->info.celldata_info.update_value
                        );
                    break;
                }

            }

            strcat(where_clause, aux_str);
        }

        for (int c = 0, is_first = true; c < content_info.num_columns; c++){
            actual_col = DataBaseManager::GetTableColData(c);
            
            if(actual_col->is_pk){
                Utils::GetStringWordAtPosition(&aux_type, actual_col->type, 0);
                if(is_first){
                    switch (DataBaseManager::StringToCellType(aux_type)){
                        case DataBaseManager::CellType::VARCHAR:
                        case DataBaseManager::CellType::CHAR:
                            sprintf(
                                aux_str,
                                "WHERE %s = '%s' ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                            break;
                        
                        default:
                            sprintf(
                                aux_str,
                                "WHERE %s = %s ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                        break;
                    }

                    is_first = false;
                }else{
                    switch (DataBaseManager::StringToCellType(aux_type)){
                        case DataBaseManager::CellType::VARCHAR:
                        case DataBaseManager::CellType::CHAR:
                            sprintf(
                                aux_str,
                                "AND %s = '%s' ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                            break;
                        
                        default:
                            sprintf(
                                aux_str,
                                "AND %s = %s ",
                                actual_col->name, 
                                TList::GetIndexListNode(actual_register,c)->info.celldata_info.db_value
                            );
                        break;
                    }
                }

                strcat(where_clause,aux_str);
            }
        }
        

        u_query = DataBaseManager::GetBaseQuery(
            DataBaseManager::BaseSQL_Querys::BASIC_UPDATE,
            TList::GetIndexListNode(TablesModule::db_tables, TablesModule::selectedTable)->info.str_info,
            where_clause
        );

        //DEBUG
        printf(
            "UPDATE QUERY:\n %s\n",
            u_query
        );
        

        //UPDATE REGISTER VALUES ASSOCIATED WITH THE BUTTON ROW BASED ON THE INPUTS AND UPDATE THE SELECTED TABLE 
        DataBaseManager::ExecuteUpdateQuery(u_query);

        free(u_query);
    }

    void DrawCellInputValue(int row, int col){
        TList::ListNode* cell = 
            TList::GetIndexListNode(
                TList::GetIndexListNode(content_info.values, row)->info.list_info, 
                col                                                                
            );
        TList::ColumnData* col_metadata = DataBaseManager::GetTableColData(col);

        char cell_label[100];
        sprintf(cell_label, "##cell_%d_%d", row, col);

        
        if (col_metadata->is_pk){
            ImGui::TableSetBgColor(
                ImGuiTableBgTarget_CellBg,
                IM_COL32(90, 90, 0, 255),
                col
            );
        }

        if(row == content_info.update_row || row == content_info.insert_row){
            if(DataBaseManager::StringToCellType(col_metadata->type) == DataBaseManager::CellType::BOOLEAN){
                bool check_value = strcmp(cell->info.celldata_info.update_value, "1") == 0;
                float cell_width = ImGui::GetContentRegionAvail().x;
                float checkbox_width = ImGui::GetFrameHeight();

                ImGui::SetCursorPosX(
                    ImGui::GetCursorPosX() + (cell_width - checkbox_width) * 0.5f
                );

                if(ImGui::Checkbox(cell_label, &check_value)){
                    strcpy(cell->info.celldata_info.update_value, check_value ? "1" : "0");
                };
            }else{
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::InputText(
                    cell_label,
                    cell->info.celldata_info.update_value,
                    col_metadata->buff_size,
                    DataBaseManager::GetInputFlagsByType(col_metadata->type)
                );
            }
        }else{
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::Text(
                cell->info.celldata_info.db_value
            );
        }
    }

    //Draws the table of the current query content. No matter if it is a custom query or a table selection
    void DrawContentTable(){
        char aux_str[100] = "\0";

        if(content_info.is_loaded && !TList::IsEmptyList(&(content_info.values))){
            if(!content_info.is_custom){
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

                    if(!content_info.is_custom){
                        if(r != content_info.insert_row && r != content_info.update_row){
                            float width = ImGui::GetContentRegionAvail().x;
                            float spacing = ImGui::GetStyle().ItemSpacing.x;
                            float button_width = (width - spacing) * 0.5f;

                            //DRAW EDIT BUTTON
                            sprintf(aux_str, "E##upd_%d", r);
                            if(ImGui::Button(aux_str, ImVec2(button_width,0))){
                                OnEditButton(r);
                            }

                            ImGui::SameLine();
                            //DRAW DELETE BUTTON
                            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(180, 60, 60, 255));
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(200, 70, 70, 255));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(160, 50, 50, 255));
                            sprintf(aux_str, "X##del_%d", r);
                            if(ImGui::Button(aux_str, ImVec2(button_width,0))){
                                OnDeleteButton(r);
                            }
                            ImGui::PopStyleColor(3);
                            
                        }else{
                            //DRAW INSERT BUTTON
                            if(r == content_info.insert_row){
                                ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(80, 180, 100, 255));
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 200, 120, 255));
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(60, 160, 80, 255));
                                if(ImGui::Button("+", ImVec2(-FLT_MIN,0))){
                                    OnInsertButton(r);
                                }
                                ImGui::PopStyleColor(3);
                            }

                            //DRAW UPDATE BUTTON
                            if(r == content_info.update_row){
                                ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(80, 180, 100, 255));
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 200, 120, 255));
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(60, 160, 80, 255));
                                if(ImGui::Button("U", ImVec2(-FLT_MIN,0))){
                                    OnUpdateButton(r);
                                }
                                ImGui::PopStyleColor(3);
                            }
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
        ImGui::SetWindowSize({Utils::kWindowWidth*0.80f, Utils::kWindowHeight*0.65f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.2f, 0.0f});

        DrawContentTable();

        ImGui::End();
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        TList::ClearList(&(content_info.values));
    }
}
