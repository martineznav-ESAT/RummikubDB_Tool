// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./Callbacks.h"

#include "../Libs/CustomLibs/Utils.h"
#include "../Libs/CustomLibs/TList.h"

namespace Callbacks{

    //Callback for BaseQuery "GetTables"
    int CB_GetTables(void *db_tables, int num_columns, char **values, char **column_names){
        TList::ListNode** tables = (TList::ListNode**) db_tables;
        TList::ListInfo aux_info;
        aux_info.str_info = (char*) malloc(sizeof(char)*strlen(values[0]));

        strcpy(aux_info.str_info, values[0]);
        if(TList::InsertList(tables, TList::ListType::STRING, aux_info)){
            printf("LOADED TABLE %s\n",values[0]);
        }else{
            printf("TABLE NOT LOADED %s\n",values[0]);
        }
        
        return 0;
    }

    //Callback for "Select * from 'tablename' Query
    int CB_SelectTableName(void *tablename, int num_columns, char **values, char **column_names){

        for (int i = 0; i < num_columns; i++){
            printf("%s | ",values[i]);
        }
        
        
        return 0;
    }
}
