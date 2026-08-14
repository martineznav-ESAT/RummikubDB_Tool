// @author Jonathan Martínez Navarro

#ifndef Callbacks_H
#define Callbacks_H

namespace Callbacks{

    //Callback for BaseQuery "GetTables"
    int CB_GetTables(void *user_param, int num_columns, char **values, char **column_names);

    //Callback for "Select * from 'tablename' Query
    int CB_SelectTableName(void *tablename, int num_columns, char **values, char **column_names);

}

#endif