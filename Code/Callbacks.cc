// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./Callbacks.h"
#include "./ScreenModules/ModulesManager.h"

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


    //Callback for "Select * from 'tablename' Query, printing the result on the ContentModule and the terminal
    int CB_SelectTableName(void *q_content_info, int num_columns, char **values, char **column_names){
        ContentModule::ContentInfo *info = (ContentModule::ContentInfo *) q_content_info;

        TList::ListInfo aux_str_info;
        aux_str_info.str_info = nullptr;

        if((info->is_loaded)){
            for (int i = 0; i < info->num_columns; i++){
                //Save "N" Row Data
                aux_str_info.str_info = (char*) malloc(sizeof(char)*strlen(values[i]));
                strcpy(aux_str_info.str_info, values[i]);
                TList::InsertList(&(info->values), TList::ListType::STRING, aux_str_info);
                info->num_rows++;
            }

        }else{
            info->num_columns = num_columns;
            info->num_rows = 0;
            TList::ClearList(&(info->column_names));
            TList::ClearList(&(info->values));

            for (int i = 0; i < info->num_columns; i++){
                //Save Column names
                aux_str_info.str_info = (char*) malloc(sizeof(char)*strlen(column_names[i]));
                strcpy(aux_str_info.str_info, column_names[i]);
                TList::InsertList(&(info->column_names), TList::ListType::STRING, aux_str_info);

                //Save First Row Data
                aux_str_info.str_info = (char*) malloc(sizeof(char)*strlen(values[i]));
                strcpy(aux_str_info.str_info, values[i]);
                TList::InsertList(&(info->values), TList::ListType::STRING, aux_str_info);
                info->num_rows++;
            }

            info->is_loaded = true;
        }
        
        return 0;
    }
}
