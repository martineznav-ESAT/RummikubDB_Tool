// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./TablesModule.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace TablesModule{
    //TablesModule Globals
    int selectedTable = -1; //Unselected by default

    //Inicialization function
    void Init(){

    }

    //Shows the available tables as interactive selectables
    void ShowAvailableTables(){

        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,ImVec2(0.0f, 0.5f));

        for (int i = 0; i < TList::ListLength(DataBaseManager::db_tables); i++){
            if (
                ImGui::Selectable(
                    TList::GetIndexListNode(DataBaseManager::db_tables, i)->info.str_info, 
                    selectedTable == i, 
                    0,
                    ImVec2(0, 25)
                )
            )
            {
                selectedTable = i;
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

    }
}
