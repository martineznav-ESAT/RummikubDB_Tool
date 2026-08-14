// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./ModulesManager.h"
#include "../DataBaseManager.h"

#include "../../Libs/CustomLibs/Utils.h"

namespace ModulesManager{
    
    //Inicialization function
    void Init(){

    }

    //Draws on screen the module determined as parameter
    void DrawScreenModule(S_Module module){
        switch (module){
            case S_Module::TABLES :
                TablesModule::Draw();
            break;

            case S_Module::QUERY_CONTENT :
                ContentModule::Draw();
            break;

            case S_Module::CUSTOM_QUERYS :
                CustomQueryModule::Draw();
            break;
        }
    }

    //Ensures everything is closed and freed from memory
    void EmptyMemory(){

    }
}
