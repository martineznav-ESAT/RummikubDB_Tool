// @author Jonathan Martínez Navarro

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TList_H
#define TList_H

namespace TList{
    enum ListType{
        INT,
        CHAR,
        STRING,
        LIST
    };

    struct ListNode;

    union ListInfo{
        int int_info;
        char char_info;
        char* str_info;
        ListNode* list_info;
    };

    struct ListNode{
        ListInfo info;
        ListType type;
        ListNode *next, *prev;
    };

    ListNode* CreateList();

    bool IsEmptyList(ListNode **list);

    //Adds a value at the beginning of the list
    bool InsertList(ListNode **list, ListType type, ListInfo info);

    //Prints the values of the list
    void PrintList(ListNode *list);

    ListNode* GetLastListNode(ListNode *list);

    ListNode* GetIndexListNode(ListNode *list, int index);

    ListNode* GetRandomListNode(ListNode *list);

    //Prints the values of the list in reverse order
    void ReverseShowList(ListNode *list);

    //Returns the number of elements in the list
    int ListLength(ListNode* list);

    //Searches for a node by value
    ListNode* FindInList(ListNode *list, ListInfo info);

    //Extracts a node from the list and returns it detached
    ListNode* ExtractFromList(ListNode **list_element);

    //Deletes a node with the given value
    // void DeleteElement(ListNode **list, ListInfo info);

    void ClearList(ListNode **list);
}

#endif
