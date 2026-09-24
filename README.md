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
<img width="1274" height="970" alt="image" src="https://github.com/user-attachments/assets/fe939d29-621f-4e0f-9a10-bb950b9750c4" />

If the database is found, it will be automatically loaded and set the tool ready to interact with.
<img width="1282" height="992" alt="image" src="https://github.com/user-attachments/assets/11a7db83-ad99-4b34-9919-aca8d6d89550" />


**USAGE**

The tool is divided in three main windows:

DB Tables -> 

Contains a vertical list of the available tables in the loaded database. Clicking one of the table names will automatically load its content and show it in the Query Content window

<img width="351" height="512" alt="image" src="https://github.com/user-attachments/assets/845a6aff-dca4-4ccd-bcc7-45ceedac016e" />


Query Content -> 

Contains the result of a select query executed either by selecting a table in the DB Tables window or a custom select executed in the Custom Querys window. 
If the shown content is from a base table, it will grant access to interactive buttons which grant the posibility of adding, updating or deleting values from the current selected table. In this situation, it will also taint in yellow the columns that represent the primary key/s of the table

<img width="1089" height="653" alt="image" src="https://github.com/user-attachments/assets/1e9f9300-9ecb-4282-8da8-0377e3cfdb13" />


Add Button

When the Add Button is clicked, creates a new row with empty values and with a new '+' button at the end that will save the new register if properly filled.

<img width="1074" height="304" alt="image" src="https://github.com/user-attachments/assets/fdeb155e-e7c5-4f71-9bb1-a777b2886a62" />


The input type of the data will limit in a basic way the possible written info based on the column value type

<img width="1137" height="623" alt="image" src="https://github.com/user-attachments/assets/10cddccc-084b-4dbd-8d12-960e97d9dacc" />

Its mainly limited to only integers, varchars (alphanumeric values) and booleans transformed as checkboxes


Update/Edit Button

Appears as an 'E' at the end of every saved register. When clicked, enables edit mode to the corresponding row, transforming the cells into inputs just as well as the Add Button does. The changes will only applie when the 'U' button is pressed

<img width="895" height="235" alt="image" src="https://github.com/user-attachments/assets/2e4e2431-14dd-483a-ab27-30e53b6d8ecc" />


Delete/X Button

Appears at the end of every register as a red button. When clicked, deletes the row value from the database instantly, no questions asked.


Custom Querys -> 

Is a text area destined to the user in which anything can be written, but when the execute button is used, it will only accept and process SELECT, UPDATE, INSERT and DELETE querys. If a select query is executed, the interactive CRUD buttons wont appear. To execute the custom querys you will need to press the Execute Query button. The Clear Query button is used to erase the text in the text area

<img width="1103" height="974" alt="image" src="https://github.com/user-attachments/assets/0c6a9edb-163e-4770-b3c3-dd507abfd8eb" />


In case of query error or not accepted query, a dialog PopUp where the error is shown will be displayed

<img width="1244" height="927" alt="image" src="https://github.com/user-attachments/assets/30a02d99-6768-42da-b849-9f2fb6c66a8a" />
<img width="1220" height="937" alt="image" src="https://github.com/user-attachments/assets/d7c33665-da63-4137-9091-3481657f8286" />
<img width="1253" height="940" alt="image" src="https://github.com/user-attachments/assets/3449e51f-7eac-484c-815b-fbb6106b3d35" />







