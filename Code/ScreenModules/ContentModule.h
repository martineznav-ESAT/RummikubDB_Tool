// @author Jonathan Martínez Navarro

#ifndef ContentModule_H
#define ContentModule_H

#include "../../Libs/CustomLibs/TList.h"

namespace ContentModule{
    struct ContentInfo{
        bool is_loaded = false;
        int num_columns, num_rows;
        //Register Row list 
        //where index 0 should correspond to the metadata/column types
        //the last one should be the column names 
        //and the registers exsist in between 
        TList::ListNode *values; 
    };

    extern ContentInfo content_info;

    //Inicialization function
    void Init();

    //Draws the module window
    void Draw();

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif