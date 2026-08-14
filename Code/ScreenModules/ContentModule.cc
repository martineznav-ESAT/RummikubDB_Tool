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

    }

    void DrawContentTable(){

        if(content_info.is_loaded && TablesModule::selectedTable != -1){
            ImGui::BeginTable("content", content_info.num_columns, 
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | 
                ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            );

            for (int r = -1; r < content_info.num_rows; r++){
                if(r == -1){
                    //Draws Header value
                    if(!TList::IsEmptyList(&(content_info.column_names))){
                        for (int c = 0; c < content_info.num_columns; c++){
                            ImGui::TableSetupColumn(TList::GetIndexListNode(content_info.column_names, c)->info.str_info);
                        }
                        ImGui::TableHeadersRow();
                    }
                }else{
                    //Draws Register value
                    if(!TList::IsEmptyList(&(content_info.values))){
                        ImGui::TableNextRow();
                        for (int c = 0; c < content_info.num_columns; c++){
                            ImGui::TableNextColumn();
                            ImGui::Text("%s", TList::GetIndexListNode(content_info.values , (r*content_info.num_columns)+c)->info.str_info);
                        }
                    }
                }
            }
            
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
        TList::ClearList(&(content_info.column_names));
        TList::ClearList(&(content_info.values));
    }
}
