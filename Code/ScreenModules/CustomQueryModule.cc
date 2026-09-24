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

    void ExecuteCustomQuery(char* q_input){
        int q_result = 1;

        //Aux values for CUD queries
        char msg[256];
        int changes;
        switch (DataBaseManager::GetQueryType(q_input)){
            case DataBaseManager::QueryType::SELECT:
                // printf("SELECT QUERY\n");
                q_result = DataBaseManager::ExecuteSelectQuery(q_input, true);
                break;
            case DataBaseManager::QueryType::UPDATE:
                // printf("UPDATE QUERY\n");
                q_result = DataBaseManager::ExecuteUpdateQuery(q_input, true);
                break;

            case DataBaseManager::QueryType::INSERT:
                // printf("INSERT QUERY\n");
                q_result = DataBaseManager::ExecuteInsertQuery(q_input, true) ;
                break;

            case DataBaseManager::QueryType::DELETE:
                // printf("DELETE QUERY\n");
                q_result = DataBaseManager::ExecuteDeleteQuery(q_input, true);
                break;

            default:
                DataBaseManager::SetPopUpValues(
                    &DataBaseManager::notif_pop_up,
                    DataBaseManager::PopUpType::POP_ERROR, 
                    "Invalid query type\nValid types: SELECT, UPDATE, INSERT, DELETE\n"
                );

                break;
        }

    }

    //Draws on screen the bottom space in which the user can execute custom querys
    void Draw(){
        ImGui::Begin("Custom Querys", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.8f, Utils::kWindowHeight*0.35f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.20f, Utils::kWindowHeight*0.65f});

        ImGui::InputTextMultiline(
            "Custom Query", query_input, sizeof(char) * query_max_length, 
            ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 20), 
            ImGuiInputTextFlags_AllowTabInput
        );

        ImGui::Button("EXECUTE QUERY",ImVec2(0, ImGui::GetTextLineHeight() * 3));
        if(ImGui::IsItemClicked()){
            ExecuteCustomQuery(query_input);
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
