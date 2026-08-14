// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./CustomQueryModule.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace CustomQueryModule{

    //CustomQuerys Globals

    
    //Inicialization function
    void Init(){

    }

    //Draws on screen the bottom space in which the user can execute custom querys
    void Draw(){
        ImGui::Begin("Custom Querys", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowSize({Utils::kWindowWidth*0.671f, Utils::kWindowHeight*0.35f});
        ImGui::SetWindowPos({Utils::kWindowWidth*0.33f, Utils::kWindowHeight*0.65f});
        ImGui::End();
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){

    }
}
