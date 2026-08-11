// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./ScreenModules.h"
#include "./DataBaseManager.h"

#include "../Libs/CustomLibs/Utils.h"

namespace ScreenModules{
    //TablesModule Globals
    int selectedTable = -1; //Unselected by default

    //QueryContent Globals

    //CustomQuerys Globals

    
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
    void DrawTables(){
        //Window Init
        ImGui::Begin("Rummikub DB", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*1.0f});
        ImGui::SetWindowPos({0.0f, 0.0f});

        ShowAvailableTables();

        ImGui::End();
    }

    //Draws on the screen top space the result of the custom query or the content of the selected table
    void DrawQueryContent(){
        ImGui::Begin("Query Content", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.671f, Utils::kWindowHeight*0.65f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.33f, 0.0f});
        ImGui::End();
    }

    //Draws on screen the bottom space in which the user can execute custom querys
    void DrawCustomQuerys(){
        ImGui::Begin("Custom Querys", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.671f, Utils::kWindowHeight*0.35f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*0.65f});
        ImGui::End();
    }

    //Draws on screen the module determined as parameter
    void DrawScreenModule(S_Module module){
        switch (module){
            case S_Module::TABLES :
                DrawTables();
            break;

            case S_Module::QUERY_CONTENT :
                DrawQueryContent();
            break;

            case S_Module::CUSTOM_QUERYS :
                DrawCustomQuerys();
            break;
        }
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){

    }
}
