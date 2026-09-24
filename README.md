**RummikubDB_Tool** is a small app tool built for the basic data interactive management of an SQLite database system based on the tabletop game called Rummikub.

The application itself was coded trying to have in mind any kind of SQLite database, yet **the main objective was for this tool to be used for the database that the release pack contains**, which means that changing the database manually could result in unexpected errors.
That being said, the following User Manual will further explain how to download and use the tool properly


**USER MANUAL**

**DOWNLOAD**

To download the tool, you just need to go to the release section of this github and download the latest version, wich will always contain a compressed file. 

**INSTALLATION AND EXECUTION**
The tool does not have any installation, to use it once downloaded, you will just need to uncompress it and launch the executable file found inside. 
It will try to open the database inside the "Assets" directory with name "DB.db"
If it can't find it, the tool will execute correctly, but a crash pop up will appear mentioning the file could not be opened.

If the database is found, it will be automatically loaded and ready to interact with.

**USAGE**
The tool is divided in three main windows

DB Tables -> 
Contains a vertical list of the available tables in the loaded database. Clicking one of the table names will automatically load its content and show it in the Query Content window

Query Content -> 
Contains the result of a select query executed either by selecting a table in the DB Tables window or a custom select executed in the Custom Querys window. 
If the shown content is from a base table, it will grant access to interactive buttons which grant the posibility of adding, updating or deleting values from the current selected table

Add Button

Update/Edit Button

Delete Button

Custom Querys -> 
Is a textarea destined to the user in which anything can be written, but when the execute button is used, it will only accept and process SELECT, UPDATE, INSERT and DELETE querys.

In case of query error or not accepted query, a dialog PopUp where the error is shown will be displayed





