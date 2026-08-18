// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./CustomQueryModule.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace CustomQueryModule{

    //CustomQuerys Globals
    int query_max_length = 1024;
    char* query_input = (char*) malloc(sizeof(char) * query_max_length);

    void ClearInput(){
        for (int i = 0; i < query_max_length; i++){
            query_input[i] = '\0';
        }
    }

    //Inicialization function
    void Init(){
        ClearInput();
    }

    //Draws on screen the bottom space in which the user can execute custom querys
    void Draw(){
        ImGui::Begin("Custom Querys", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.671f, Utils::kWindowHeight*0.35f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*0.65f});

        ImGui::InputTextMultiline(
            "Custom Query", query_input, sizeof(char) * query_max_length, 
            ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 20), 
            ImGuiInputTextFlags_AllowTabInput
        );

        ImGui::Button("EXECUTE QUERY",ImVec2(0, ImGui::GetTextLineHeight() * 3));
        if(ImGui::IsItemClicked()){
            switch (DataBaseManager::GetQueryType(query_input)){
                case DataBaseManager::QueryType::SELECT:
                    printf("SELECT QUERY\n");
                    ContentModule::content_info.is_loaded = false;
                    DataBaseManager::QueryErrorManager(
                        DataBaseManager::ExecuteSelectQuery(query_input, true), 
                        DataBaseManager::error_msg
                    );
                    break;
                case DataBaseManager::QueryType::UPDATE:
                    /* TO_DO */
                    printf("UPDATE QUERY\n");
                    break;
                case DataBaseManager::QueryType::INSERT:
                    /* TO_DO */
                    printf("INSERT QUERY\n");
                    break;
                case DataBaseManager::QueryType::DELETE:
                    /* TO_DO */
                    printf("DELETE QUERY\n");
                    break;
                default:
                    /*TO_DO*/
                    printf("ERROR: Invalid query type\n");
                    printf("Valid types: SELECT, UPDATE, INSERT, DELETE\n");
                    break;
            }
        }
        ImGui::SameLine();
        ImGui::Button("CLEAR QUERY",ImVec2(0, ImGui::GetTextLineHeight() * 3));
        if(ImGui::IsItemClicked()){
            ClearInput();
        }

        ImGui::End();
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){
        free(query_input);
    }
}
