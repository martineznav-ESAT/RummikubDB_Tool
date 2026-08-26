// @author Jonathan Martínez Navarro

#ifndef TablesModule_H
#define TablesModule_H

#include "../DataBaseManager.h"
#include "../Callbacks.h"

#include "../../Libs/CustomLibs/Utils.h"
#include "../../Libs/CustomLibs/TList.h"

namespace TablesModule{
    extern TList::ListNode* db_tables;
    extern int selectedTable; 

    //Inicialization function
    void Init();

    //Draws the module window
    void Draw();

    //Function that executes the basic select query for the table selected at the moment
    void CallSelectedTableQuery();

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif