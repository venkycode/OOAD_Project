#include <sqlite3.h> 
#include <bits/stdc++.h>
#include "header.h"

using namespace std;
//Dont forget to close database 

class admin{
    sqlite3* DB;
    int exit; 
    string data;
    char* messaggeError; 
    int shopKeeperCount,deliveryPersonCount,CustomerCount;
    static int callback(void* data, int argc, char** argv, char** azColName) 
    { 
        int i; 
        fprintf(stderr, "%s: ", (const char*)data); 
    
        for (i = 0; i < argc; i++) { 
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
        } 
    
        printf("\n"); 
        return 0; 
    }

    void createDataBase(){
        int exit = 0; 
        shopKeeperCount=deliveryPersonCount=CustomerCount=0;
        exit = sqlite3_open("userDatabase.db", &DB);
        if (exit) { 
            cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
            std::exit(1); 
        } 
        else
            std::cout << "Created Database Successfully!" << std::endl; 
        string sql = "CREATE TABLE PERSON("
                      "ID TEXT PRIMARY KEY     NOT NULL, "
                      "NAME           TEXT    NOT NULL, "
                      "SURNAME          TEXT     NOT NULL, "
                      "EMAIL_ID      TEXT     NOT NULL, "
                      "ADDRESS        CHAR(50), "
                      "USERNAME      TEXT   NOT NULL,"
                      "PASSWORD     TEXT     NOT NULL);"; 
        string sql2="CREATE TABLE TRANSACTION("
                                                "ID TEXT PRIMARY KEY     NOT NULL, "
                                                "TRANSACTIONS  TEXT  NOT NULL );";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);  
        exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);  
        if (exit != SQLITE_OK) { 
            std::cerr << "Error Create Table" << std::endl; 
            sqlite3_free(messaggeError); 
        } 
        else
            std::cout << "Table created Successfully" << std::endl;
    }

    void loadDatabase(){
        int exit = 0; 
        exit = sqlite3_open("userDatabase.db", &DB);
        if (exit) 
            createDataBase(); 
        else
            std::cout << "Opened Database Successfully!" <<endl; 
        string data("CALLBACK FUNCTION"); 
    }

    void Insert(string name,string surname,string email,string address, string username,string password,enum typeOfUser type){
        string id="";
        if(type==Customer){
            id='C'+to_string(CustomerCount++);
        }
        else if(type == deliveryPerson){
            id='D'+to_string(deliveryPersonCount++);
        }
        else {
            id='S'+to_string(shopKeeperCount++);
        }
        string sql("INSERT INTO PERSON VALUES(id, name, surname, email, address, username,password);");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
        if (exit != SQLITE_OK) { 
            std::cerr << "Error Insert" << std::endl; 
            sqlite3_free(messaggeError); 
        } 
        else
            std::cout << "Record inserted Successfully!" << std::endl; 
    }

    void Delete(string id){
        string sql = "DELETE FROM PERSON WHERE ID="+id+";"; 
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
        if (exit != SQLITE_OK) { 
            std::cerr << "Error DELETE" << std::endl; 
            sqlite3_free(messaggeError); 
        } 
        else
            std::cout << "Record deleted Successfully!" << std::endl; 
    }

    void update(string id){
        string sql = "UPDATE FROM TRANSACTION WHERE ID="+id+";";
        
    }
};
int main(){
     
    int loda=1;
    string chut=to_string(loda);
    string sql("SELECT * FROM PERSON WHERE ID="+chut+";"); 
    

    int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL); 
  
    if (rc != SQLITE_OK) 
        cerr << "Error SELECT" << endl; 
    else { 
        cout << "Operation OK!" << endl; 
    } 
    sqlite3_close(DB); 
}