// @author Jonathan Martínez Navarro

#include <esat_extra/imgui.h>

#include "./Callbacks.h"
#include "./ScreenModules/ModulesManager.h"

#include "../Libs/CustomLibs/Utils.h"
#include "../Libs/CustomLibs/TList.h"

namespace Callbacks{

    bool is_callback_called = false;

    //Callback for BaseQuery "GetTables"
    int CB_GetTables(void *db_tables, int num_columns, char **values, char **column_names){
        TList::ListNode** tables = (TList::ListNode**) db_tables;
        TList::ListInfo aux_info;

        aux_info.str_info = (char*) malloc(sizeof(char) * (strlen(values[0])+1));
        strcpy(aux_info.str_info, values[0]);
        
        if(TList::InsertList(tables, TList::ListType::STRING, aux_info)){
            strupr(aux_info.str_info);
        }
        
        return 0;
    }


    //Callback for any "Select-Type" Query, printing the result on the ContentModule and the terminal
    int CB_SelectQuery(void *q_content_info, int num_columns, char **values, char **column_names){
        ContentModule::ContentInfo *info = (ContentModule::ContentInfo *) q_content_info;

        TList::ListInfo aux_str_info;
        aux_str_info.str_info = nullptr;

        is_callback_called = true;

        if((info->is_loaded)){
            for (int i = (info->num_columns)-1; i >= 0 ; i--){
                //Save N Row Data
                if(values[i] == nullptr){
                    aux_str_info.str_info = (char*) malloc(sizeof(char) * (strlen("NULL")+1));
                    strcpy(aux_str_info.str_info, "NULL");
                }else{
                    aux_str_info.str_info = (char*) malloc(sizeof(char) * (strlen(values[i])+1));
                    strcpy(aux_str_info.str_info, values[i]);
                }
                TList::InsertList(&(info->values), TList::ListType::STRING, aux_str_info);
            }

        }else{
            info->num_columns = num_columns;
            info->num_rows = 0;
            TList::ClearList(&(info->column_names));
            TList::ClearList(&(info->values));

            for (int i = (info->num_columns)-1; i >= 0 ; i--){
                //Save Column names
                aux_str_info.str_info = (char*) malloc(sizeof(char) * (strlen(column_names[i])+1));
                strcpy(aux_str_info.str_info, column_names[i]);
                TList::InsertList(&(info->column_names), TList::ListType::STRING, aux_str_info);

                //Save First Row Data
                if(values[i] == nullptr){
                    aux_str_info.str_info = (char*) malloc(sizeof(char) * (strlen("NULL")+1));
                    strcpy(aux_str_info.str_info, "NULL");
                }else{
                    aux_str_info.str_info = (char*) malloc(sizeof(char) * (strlen(values[i])+1));
                    strcpy(aux_str_info.str_info, values[i]);
                }
                TList::InsertList(&(info->values), TList::ListType::STRING, aux_str_info);
            }
            info->is_loaded = true;
        }
        info->num_rows++;

        //DEBUG
        // printf("%p\n",info);
        // for (int i = 0; i < info->num_columns; i++)
        // {
        //     printf("%s ",TList::GetIndexListNode(info->column_names, i)->info.str_info);
        // }
        // printf("\n");
        // for (int i = 0; i < TList::ListLength(info->values); i++)
        // {
        //     printf("%s ",TList::GetIndexListNode(info->values, i)->info.str_info);
        //     if((i+1)%info->num_columns == 0 && i!=0){
        //         printf("\n");
        //     }
        // }
        // printf("\n");
        
        
        return 0;
    }
}
