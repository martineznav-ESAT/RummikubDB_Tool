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

        TList::ListInfo info_aux;
        TList::ListNode* row_aux;
        TList::ListInfo row_info_aux;

        is_callback_called = true;

        //If there's been at least 1 row loaded already...
        if((info->is_loaded)){
            //Save N Row Data
            row_aux = TList::CreateList();
            for (int i = (info->num_columns)-1; i >= 0 ; i--){
                //Save First Row Data
                if(values[i] == nullptr){
                    info_aux.str_info  = (char*) malloc(sizeof(char) * (strlen("NULL")+1));
                    strcpy(info_aux.str_info , "NULL");
                }else{
                    info_aux.str_info = (char*) malloc(sizeof(char) * (strlen(values[i])+1));
                    strcpy(info_aux.str_info, values[i]);
                }
                TList::InsertList(
                    &row_aux, 
                    TList::ListType::STRING,
                    info_aux
                );
            }
            //Save N register in table given as parameter
            row_info_aux.list_info = row_aux;
            TList::InsertList(
                &(info->values), 
                TList::ListType::LIST,
                row_info_aux
            );

        }else{
            //First Row Loaded
            info->num_columns = num_columns;
            info->num_rows = 0;
            TList::ClearList(&(info->values));

            row_aux = TList::CreateList();
            for (int i = (info->num_columns)-1; i >= 0 ; i--){
                //Saves Column Names 
                info_aux.str_info = (char*) malloc(sizeof(char) * (strlen(column_names[i])+1));
                strcpy(info_aux.str_info, column_names[i]);
                TList::InsertList(
                    &row_aux, 
                    TList::ListType::STRING,
                    info_aux
                );
            }
            //Save colnames in table given as parameter
            row_info_aux.list_info = row_aux;
            TList::InsertList(
                &(info->values), 
                TList::ListType::LIST,
                row_info_aux
            );

            row_aux = TList::CreateList();
            for (int i = (info->num_columns)-1; i >= 0 ; i--){
                //Save First Row Data
                if(values[i] == nullptr){
                    info_aux.str_info  = (char*) malloc(sizeof(char) * (strlen("NULL")+1));
                    strcpy(info_aux.str_info , "NULL");
                }else{
                    info_aux.str_info = (char*) malloc(sizeof(char) * (strlen(values[i])+1));
                    strcpy(info_aux.str_info, values[i]);
                }
                TList::InsertList(
                    &row_aux, 
                    TList::ListType::STRING,
                    info_aux
                );
            }
            //Save first register in table given as parameter
            row_info_aux.list_info = row_aux;
            TList::InsertList(
                &(info->values), 
                TList::ListType::LIST,
                row_info_aux
            );


            info->is_loaded = true;
        }

        return 0;
    }
}
