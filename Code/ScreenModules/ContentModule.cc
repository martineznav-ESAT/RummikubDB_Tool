// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./ContentModule.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace ContentModule{
    //QueryContent Globals
    ContentInfo content_info;
    
    //Inicialization function
    void Init(){
        content_info.is_loaded = false;
        content_info.num_columns = 0;
        content_info.num_rows = 0;
        content_info.values = TList::CreateList();
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
        // printf(
        //     "DELETE QUERY:\n %s\n",
        //     d_query
        // );
        

        //DELETE REGISTER VALUE ASSOCIATED WITH THE BUTTON ROW AND UPDATE THE TABLE SELECT
        DataBaseManager::ExecuteDeleteQuery(d_query);

        TablesModule::CallSelectedTableQuery();
    }

    //Draws the table of the current query content. No matter if it is a custom query or a table selection
    void DrawContentTable(){

        if(content_info.is_loaded && !TList::IsEmptyList(&(content_info.values))){
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
                    ImGui::TableSetupColumn("");
                    ImGui::TableHeadersRow();
                }else{
                    //Draws Register value
                    ImGui::TableNextRow();
                    for (int c = 0; c < content_info.num_columns; c++){
                        ImGui::TableNextColumn();
                        ImGui::Text(
                            "%s", 
                            TList::GetIndexListNode(
                                TList::GetIndexListNode(content_info.values, r)->info.list_info, //Row
                                c                                                                //Col
                            )->info.str_info
                        );
                    }
                    ImGui::TableNextColumn();

                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(180, 60, 60, 255));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(200, 70, 70, 255));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(160, 50, 50, 255));
                    if(ImGui::Button("X", ImVec2(-1,0))){

                        OnDeleteButton(r);
                    }
                    ImGui::PopStyleColor(3);
                }
            }

            //DEBUG
            // printf("END DRAW CONTENT TABLE\n");
            
            
            ImGui::EndTable();
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
