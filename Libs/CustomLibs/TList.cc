// @author Jonathan Martínez Navarro

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "./TList.h"

namespace TList{

    //List constructor
    ListNode* CreateList(){
        return nullptr;
    }

    //Returns a boolean that determines if the given list is empty or not
    bool IsEmptyList(ListNode **list){
        return (*list == nullptr);
    }

    //Searches for a node by value
    ListNode* FindInList(ListNode *list, ListInfo info){
        ListNode *aux = nullptr;
        // printf("FindInList\n");
        if(list != nullptr){
            switch (list->type){
                case ListType::INT:
                    for(aux = list; aux != nullptr && aux->info.int_info != info.int_info; aux = aux->next);
                break;
            
                case ListType::CHAR:
                    for(aux = list; aux != nullptr && aux->info.char_info != info.char_info; aux = aux->next);
                break;

                case ListType::STRING:
                    for(aux = list; aux != nullptr && strcmp(aux->info.str_info, info.str_info) != 0; aux = aux->next);
                break;
            }
        }

        //DEBUG
        // if(aux == nullptr){
        //     printf(" >>> Not found in list\n");
        // }else{
        //     printf(" >>> Found in list\n");
        // }
        
        return aux;
    }

    //Adds a value at the beginning of the list. 
    //Returns a bool that determines if the value was properly inserted
    bool InsertList(ListNode **list, ListType type, ListInfo info){
        bool is_inserted = true;
        ListNode *aux;
        // printf("InsertList\n");
        aux = (ListNode*) malloc(sizeof(ListNode));
        aux->info = info;
        aux->type = type;
        aux->next = *list;
        aux->prev = nullptr;

        if(*list != nullptr){
            (*list)->prev = aux;
        }

        *list = aux;

        return is_inserted;
    }    


    //Prints the values of one ListNode
    void PrintNodeInfo(ListNode *list){
        switch (list->type){
            case ListType::INT:
                printf("%d | ",list->info.int_info);
            break;
        
            case ListType::CHAR:
                printf("%c | ",list->info.char_info);
            break;

            case ListType::STRING:
                printf("%s | ",list->info.str_info);
            break;
        }
    }

    //Prints the values of the whole list
    void PrintList(ListNode *list){
        printf("PRINTING TLIST\n");
        for(ListNode *p = list; p!=nullptr; p = p->next){
            PrintNodeInfo(p);
        }
        printf("\n");
    }

    //Returns the last node of the given list
    ListNode* GetLastListNode(ListNode *list){
        ListNode *aux = nullptr;
        if(list != nullptr){
            for(aux = list; aux->next != nullptr; aux = aux->next);
        }
        return aux;
    }

    //Returns the node of a list based on the given index
    ListNode* GetIndexListNode(ListNode *list, int index){
        ListNode *aux = nullptr;
        int i = 0;
        for(aux = list; aux != nullptr && i != index; aux = aux->next, i++);
        return aux;
    }

    //Returns a random node of the given list
    ListNode* GetRandomListNode(ListNode *list){
        ListNode *aux = nullptr;
        int random_i = rand()%ListLength(list);
        int i = 0;
        for(aux = list; aux != nullptr && i != random_i; aux = aux->next, i++);
        return aux;
    }

    //Prints the values of the list in reverse order
    void ReverseShowList(ListNode *list){
        ListNode *aux = GetLastListNode(list);

        //Second traversal backwards printing info
        while(aux != nullptr){
            PrintNodeInfo(aux);
            aux = aux->prev;
        }
    }

    //Returns the number of elements in the list
    int ListLength(ListNode* list){
        int res = 0;

        for(ListNode *p = list; p!=nullptr; p = p->next){
            res++;
        }

        return res;
    }

    //Extracts a node from the list and returns it detached
    ListNode* ExtractFromList(ListNode **list_element){
        ListNode *aux_act = *list_element;
        ListNode *aux_next = (*list_element)->next;
        ListNode *aux_prev = (*list_element)->prev;

        if(aux_prev != nullptr){
            aux_prev->next = aux_next;
        }
        if(aux_next != nullptr){
            aux_next->prev = aux_prev;
        }

        (*list_element)->next = nullptr;
        (*list_element)->prev = nullptr;

        if(aux_prev == nullptr){
            *list_element = aux_next;
        }
        
        return aux_act;
    }

    //Deletes the given node from the list
    void DeleteElement(ListNode **list, ListNode *delete_node){
        // printf("DeleteFromList\n");

        //Check if exists
        if(IsEmptyList(&delete_node)){
            printf(" >>> Not found in list\n");
        }else{
            //If exists, extract it
            if(delete_node == *list){
                delete_node = ExtractFromList(list);
            }else{
                delete_node = ExtractFromList(&delete_node);
            }

            switch (delete_node->type){
                case ListType::STRING:
                    free(delete_node->info.str_info);
                break;
            }

            //Free memory
            free(delete_node);
        }
    }

    //Deletes a node with the given value
    // void DeleteElement(ListNode **list, ListInfo info){
    //     // printf("DeleteFromList\n");
        
    //     ListNode *aux = FindInList(*list, info);
    //     DeleteElement(list, aux);
    // }

    //Cleans a list completely deleting all the nodes inside it 
    void ClearList(ListNode **list){
        // printf("CLEAR LIST\n");
        for(ListNode *act = *list; !IsEmptyList(list); act = *list){
            DeleteElement(list, act);
        }
        *list = CreateList();
        // printf("CLEAR LIST COMPLETED\n");
    }
}
