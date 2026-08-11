// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./ScreenModules.h"

#include "../Libs/CustomLibs/Utils.h"

namespace ScreenModules{
    char* db_tables[] = {"Tabla1", "Tabla2", "Tabla3"};
    int selectedTable = 0;

    //Inicialization function
    void Init(){

    }

    //Draws on screen the left column that portraits the available tables of the database
    void DrawTables(){

        ImGui::Begin("Rummikub DB", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*1.0f});
        ImGui::SetWindowPos({0.0f, 0.0f});

        for (int i = 0; i < 3; i++){
            if (ImGui::Selectable(db_tables[i], selectedTable == i))
            {
                selectedTable = i;
            }
        }

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

    //Inicialization function
    void EmptyMemory(){

    }
}
