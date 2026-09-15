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
        COLUMNDATA,
        CELLDATA,
        LIST
    };

    struct ListNode;

    struct ColumnData{
        char name[80];
        char type[50];
        int buff_size;
    };

    struct CellData{
        //The row value should be inverted. Meaning that if row value is 0, its actual index in the list will be ListLength - 1
        //In other words, row_index = (ListLength - 1) - CellData.row
        //This happens because every time a value is inserted in the list, it will always begin at index 0 but change as more values are getting inserted
        //With this simple equation, we can store the current length of the list before inserting the new value, storing the perfect reference for us tu calculate it later if needed
        int row; 
        int col; 
        char* db_value;
        char* update_value;
    };

    union ListInfo{
        int int_info;
        char char_info;
        char* str_info;
        ColumnData coldata_info;
        CellData celldata_info;
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

    //Deletes the given node from the list
    void DeleteElement(ListNode **list, ListNode *delete_node);

    //Deletes a node at the given index
    void DeleteElement(ListNode **list, int index);


    //Deletes a node with the given value
    // void DeleteElement(ListNode **list, ListInfo info);

    void ClearList(ListNode **list);
}

#endif
