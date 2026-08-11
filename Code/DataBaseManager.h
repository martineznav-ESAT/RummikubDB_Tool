// @author Jonathan Martínez Navarro
#include "../Libs/CustomLibs/TList.h"

#ifndef DataBaseManager_H
#define DataBaseManager_H

namespace DataBaseManager{
    extern TList::ListNode* db_tables;

    enum BaseSQL_Querys{
        GET_TABLES,
        TOTAL_QUERYS
    };

    //Inicialization function
    void Init();

    //Ensures everything is closed and freed from memory
    void EmptyMemory();
}

#endif