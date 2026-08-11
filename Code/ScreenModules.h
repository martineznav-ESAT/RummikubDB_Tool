// @author Jonathan Martínez Navarro

#ifndef ScreenModules_H
#define ScreenModules_H

namespace ScreenModules{

    enum S_Module{
        TABLES,
        CUSTOM_QUERYS,
        QUERY_CONTENT,
        TOTAL_S_MODULES
    };

    //Inicialization function
    void Init();

    //Draws on screen the module determined as parameter
    void DrawScreenModule(S_Module module);

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif