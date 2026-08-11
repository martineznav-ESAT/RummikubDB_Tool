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

#include "./Code/ScreenModules.h"

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

    ScreenModules::DrawScreenModule(ScreenModules::S_Module::TABLES);
    ScreenModules::DrawScreenModule(ScreenModules::S_Module::QUERY_CONTENT);
    ScreenModules::DrawScreenModule(ScreenModules::S_Module::CUSTOM_QUERYS);

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

//Main function
int esat::main(int argc, char **argv) {
    Utils::GenerateRandomSeed();

	esat::WindowInit(Utils::kWindowWidth, Utils::kWindowHeight);
	WindowSetMouseVisibility(true);

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