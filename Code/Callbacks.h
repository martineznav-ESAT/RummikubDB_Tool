// @author Jonathan Martínez Navarro

#ifndef Callbacks_H
#define Callbacks_H

namespace Callbacks{

    //Global variable used to determine manually if a callback has been called. 
    //Usually used to check if a select is valid but returns no registers
    //Has to be manually be turned to false before any sqlite_exec that uses a potential callback that may return no values 
    //And turned to true at the beginning of every potential callback  
    extern bool is_callback_called;

    //Callback for BaseQuery "GetTables"
    int CB_GetTables(void *user_param, int num_columns, char **values, char **column_names);

    //Callback for "Select * from 'tablename' Query
    int CB_SelectTableName(void *tablename, int num_columns, char **values, char **column_names);

}

#endif