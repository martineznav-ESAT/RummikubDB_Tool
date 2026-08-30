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

    //Draws the table of the current query content. No matter if it is a custom query or a table selection
    void DrawContentTable(){

        if(content_info.is_loaded && !TList::IsEmptyList(&(content_info.values))){
            ImGui::BeginTable("content", content_info.num_columns, 
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | 
                ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            );

            //DEBUG
            // printf("\nSTART DRAW CONTENT TABLE\n");
            // TList::PrintList(content_info.values);
            for (int r = content_info.num_rows-1; r > 0; r--){
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
                            )->info.str_info
                        );
                    }
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
