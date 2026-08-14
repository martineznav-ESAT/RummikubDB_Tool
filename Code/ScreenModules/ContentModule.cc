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
        if(content_info.is_loaded && TablesModule::selectedTable > -1){
            printf("DRAWING CONTENT\n");
            ImGui::BeginTable("content", content_info.num_columns);

            for (int r = 0; r < content_info.num_rows; r++){
                ImGui::TableNextRow();
                for (int c = 0; c < content_info.num_columns; c++){
                    ImGui::TableNextColumn();
                    if(r == 0){
                        //Draws Header value
                        ImGui::Text("%s", TList::GetIndexListNode(content_info.column_names, r)->info.str_info);
                    }else{
                        //Draws Register value
                        ImGui::Text("%s", TList::GetIndexListNode(content_info.values , (r*content_info.num_columns)+c)->info.str_info);
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
