// @author Jonathan Martínez Navarro 

#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat_extra/imgui.h>

#include "./Libs/CustomLibs/AudioLib.h"
#include "./Libs/CustomLibs/Utils.h"

// Launches all Initialization functions needed from all the imported resources.
void Init(){
    AudioLib::Init();
    // printf("INIT GAME END\n");
}

// Launches the current screen update functions needed 
void Update(){

}

// Launches the current screen draw functions needed 
void Draw(){
    esat::DrawClear(0,0,0);

    ImGui::Begin("Rummikub DB");
    ImGui::SetWindowSize({Utils::kWindowWidth*0.98f, Utils::kWindowHeight*0.48f});
    ImGui::SetWindowPos({Utils::kWindowWidth*0.01f,Utils::kWindowHeight*0.01f});
    ImGui::End();

    ImGui::Begin("Custom Querys");
    ImGui::SetWindowSize({Utils::kWindowWidth*0.98f, Utils::kWindowHeight*0.48f});
    ImGui::SetWindowPos({Utils::kWindowWidth*0.01f,Utils::kWindowHeight*0.51f});
    ImGui::End();

    esat::DrawEnd();  	
}

//Returns a boolean that determines if the conditions to close the game are succeeded
bool CloseCondition(){
    return (
        esat::WindowIsOpened() && 
        !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)
    );
}

// Launches all memory releasing functions needed from all the imported resources.
void EmptyMemory(){
    AudioLib::EmptyMemory();
    //printf("AudioLib FINO\n");
}

//Ensures all the posibly used files are closed
void CloseFiles(){

}

int esat::main(int argc, char **argv) {
    Utils::GenerateRandomSeed();

	esat::WindowInit(Utils::kWindowWidth, Utils::kWindowHeight);
	WindowSetMouseVisibility(true);

    esat::DrawSetTextFont("./Assets/Fonts/Hyperspace.ttf");

    Init();

    while(CloseCondition()) {        
        Utils::last_time = esat::Time();

        esat::DrawBegin();

        Update();
        Draw();

        ImGui::Render();
        esat::WindowFrame();

        Utils::ControlFps();
    }

    
    CloseFiles();
    EmptyMemory();
    
    printf("TOOL CLOSED CORRECTLY\n");
    
    esat::WindowDestroy();

    return 0;  
}