#include<Python.h>
#include <sqlite3.h>
#include <bits/stdc++.h>
#include "header.h"
#include "checks.h"
#include "sha256.h"

using namespace std;
//Dont forget to close database

class admin
{
    static sqlite3 *DB;
    static int exit;
    static string data;
    static char *messaggeError;
    static int shopKeeperCount, deliveryPersonCount, CustomerCount; // helps in assigning the ID to everyone
    static string add;                                              //used for adding transactions
    static string temporaryID;                                      // also helps in adding transactions
    static profile temporaryProfile;                                // helps in editing profile
    static product *global_inventory_array;
    static vector<product> global_inventory; //mapping from product name to product
    //static product* personal_inventory;
    ifstream global_inve_file;
    //ifstream personal_inventory_file;
    static map<string, vector<int>> personal_inventory; // shopkeeper id mapped to vector of productsID owned by him
    static vector<vector<product>> productId_to_product; 
    static string temporaryPassword;
    static int callback(void *data, int argc, char **argv, char **azColName)
    {
        int i;
        fprintf(stderr, "%s: ", (const char *)data);

        for (i = 0; i < argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");
        return 0;
    }

    static int update(void *data, int argc, char **argv, char **azColName)
    {
        int n = strlen(argv[0]) + add.size();
        int originalLength = strlen(argv[0]);
        char *tmp = (argv[0] + originalLength);
        tmp = (char *)malloc(sizeof(char) * n);
        for (int i = originalLength; i < n; ++i)
            argv[0][i] = add[i - originalLength];
        string sql = "UPDATE set TRANSACTION = \'" + string(argv[0]) + "\' WHERE ID = " + temporaryID;
        sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
        return 0;
    }

    static int get_information(void *data, int argc, char **argv, char **azColName)
    {
        temporaryProfile.name = argv[1];
        temporaryProfile.surname = argv[2];
        temporaryProfile.email = argv[3];
        temporaryProfile.address = argv[4];
        temporaryProfile.username = argv[5];
        temporaryProfile.password = argv[6];
        return 0;
    }

    static int check_username(void* data, int argc, char** argv, char** azColName) 
    { 
        temporaryID = argv[0] ? argv[0] : "#";
        return 0;
    }
    static int get_username(void* data, int argc, char** argv, char** azColName) 
    { 
        temporaryID=argv[2] && argv[1] == temporaryPassword ? argv[2]: "#";
        return 0;
    }

    void createDataBase(){
        int exit = 0; 
        shopKeeperCount=deliveryPersonCount=CustomerCount=0;
        exit = sqlite3_open("userDatabase.db", &DB);
        if (exit)
        {
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
                     "CONTACT_NO   TEXT  NOT NULL,"
                     "USERNAME      TEXT   NOT NULL,"
                     "PASSWORD     TEXT     NOT NULL);";
        string sql2 = "CREATE TABLE TRANSACTION("
                      "ID TEXT PRIMARY KEY     NOT NULL, "
                      "TRANSACTIONS  TEXT  NOT NULL );";
        string sql3 = "CREATE TABLE USER_MAP("
                      "USERNAME TEXT PRIMARY KEY     NOT NULL, "
                      "ID  TEXT  NOT NULL );";

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql3.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error Create Table" << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Table created Successfully" << endl;
    }

    void loadDatabase()
    {
        int exit = 0;
        exit = sqlite3_open("userDatabase.db", &DB);
        if (exit)
            createDataBase();
        else
            std::cout << "Opened SQL Database Successfully!" << endl;
        string data("CALLBACK FUNCTION");

        global_inve_file.open("gobal_inventory_db", ios::binary);

        int size=getFileSize("global_inventory_db") / sizeof(product);
        
        global_inventory_array = (product *)malloc(size* sizeof(product));
        
        global_inve_file.read((char *)global_inventory_array, sizeof(getFileSize("global_inventory_db")));

        for(int i = 0 ; i < size ; ++i){
            global_inventory.push_back(global_inventory_array[i]);
            personal_inventory[global_inventory_array[i].shopkeeper_id].push_back(global_inventory_array[i].product_id);
            productId_to_product[global_inventory_array[i].product_id].push_back(global_inventory_array[i]);
        }
        
        /*personal_inventory_file.open("personal_inventory_db", ios::binary);
        product *dummy = (product *)malloc(size);
        personal_inventory_file.read((char *)dummy, size * sizeof(product));
        int i = 0;
        while (i < size)
        {
            product *tmp;
            tmp = dummy + i;
            if (personal_inventory.find(string(tmp->shopkeeper_id)) != personal_inventory.end())
            {
                product p = *tmp;
                personal_inventory[string(tmp->shopkeeper_id)].push_back(p);
            }
        }*/
    }

    void Insert(string name, string surname, string email, string address, string username, string password, string contact, enum typeOfUser type)
    {
        string id = "";
        if (type == Customer)
        {
            id = 'C' + to_string(CustomerCount++);
        }
        else if (type == deliveryPerson)
        {
            id = 'D' + to_string(deliveryPersonCount++);
        }
        else
        {
            id = 'S' + to_string(shopKeeperCount++);
        }
        string sql("INSERT INTO PERSON VALUES(id, name, surname, email, address,contact, username,password);");
        string sql1("INSERT INTO USER_MAP(username,id);");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error Insert" << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Record inserted Successfully!" << endl;
    }

    void deleteID(string id){
        string sql = "DELETE FROM PERSON WHERE ID="+id+";"; 
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 
        if (exit != SQLITE_OK) { 
            cerr << "Error DELETE" << endl; 
            sqlite3_free(messaggeError); 
        } 
        else
            cout << "Record deleted Successfully!" << endl;
    }
    // isPaid is 0 if money is refunded else it is 1;
    void addTransaction(string id,bool isPaid,int moneyTransferred,int orderID){
        string query = "SELECT TRANSACTION FROM TRANSACTION WHERE ID="+id+";";
        string add = to_string(orderID)+" | "+ (isPaid?"Paid":"Refunded") + " | "+ to_string(moneyTransferred)+"\n";
        temporaryID=id;
        sqlite3_exec(DB, query.c_str(),update, NULL, NULL); 
    }

    void changeProfile(string id, string name, string surname, string email, string address, string username, string password)
    {
        string sql = "DELETE FROM PERSON WHERE ID=" + id + ";";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Record deleted Successfully!" << endl;
        string sql1("INSERT INTO PERSON VALUES(id, name, surname, email, address,contact, username,password);");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error Insert" << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Record inserted Successfully!" << endl;
    }

    void editProfile(string id)
    {
        string query = "SELECT * FROM PERSON WHERE ID=" + id + ";";
        sqlite3_exec(DB, query.c_str(), get_information, NULL, NULL);
        char check;
        cout << "Do you wish to change your name?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            string new_name;
            cin >> new_name;
            temporaryProfile.name = new_name;
        }
        cout << "Do you wish to change your Surname?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            string new_surname;
            cin >> new_surname;
            temporaryProfile.surname = new_surname;
        }
        cout << "Do you wish to change your Email ID?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            string new_email;
            cin >> new_email;
            while (!isEmailCorrect(new_email))
            {
                cout << "Enter a valid Email address(Only IIT Jodhpur official email addresses are considered valid) ";
                cin >> new_email;
            }
            temporaryProfile.email = new_email;
        }
        cout << "Do you wish to change your address?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            string new_address;
            cin >> new_address;
            temporaryProfile.name = new_address;
        }
        cout << "Do you wish to change your Contact number?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            string new_contact;
            cin >> new_contact;
            while (!isContactCorrect(new_contact))
            {
                cout << "Enter a valid contact number";
                cin >> new_contact;
            }
            temporaryProfile.name = new_contact;
        }
        cout<<"Do you wish to change your Password?(Y/n) :: ";
        cin>>check;
        if(check=='Y'||check=='y'){
            string new_password, confirm_new_password;
            cin>>new_password;
            cout<<"Confirm Password: ";
            cin>>confirm_new_password;
            while(!(isPasswordCorrect(new_password)&&confirm_new_password==new_password)){
                cout<<"Enter a valid Password: "; 
                cin>>new_password;
                cout<<"Confirm Password: ";
                cin>>confirm_new_password;
            }
            temporaryProfile.name = new_password;
        }
        changeProfile(id,temporaryProfile.name,temporaryProfile.surname,temporaryProfile.email,temporaryProfile.address,temporaryProfile.username,temporaryProfile.password);
    }

    profile authenticate(string username,string password){
        string query = "SELECT * FROM USER_MAP WHERE USERNAME = "+username+";";
        int rc=sqlite3_exec(DB, query.c_str(),get_username, NULL, NULL);
        if (rc != SQLITE_OK || temporaryID=="#"){ 
            cerr << "Error SELECT" << endl; 
            cout<<"INCORRECT Username or Password"<<endl;
            temporaryProfile.name="#";
            return temporaryProfile;
        }
        else { 
            cout << "Operation OK!" << endl; 
        }
        temporaryProfile.id=temporaryID;
        query = "SELECT * FROM PERSON WHERE ID = "+temporaryID+";";
        sqlite3_exec(DB, query.c_str(),get_information, NULL, NULL);
        return temporaryProfile;
    }
    // 1 -> signup done else Username already exists
    void showTransaction(string id){
        string query = "SELECT TRANSACTIONS FROM TRANSACTION WHERE ID = "+id+";";
        int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); 
        if (rc != SQLITE_OK) 
            cerr << "Error SELECT" << endl; 
        else { 
            cout << "Operation OK!" << endl; 
        } 
    }

    bool signUp(profile addToDatabase){
        string query = "SELECT ID FROM USER_MAP WHERE USERNAME = "+addToDatabase.username+";";
        int rc=sqlite3_exec(DB, query.c_str(),check_username, NULL, NULL);
        if(temporaryID=="#"){
            Insert(addToDatabase.name,addToDatabase.surname,addToDatabase.email,\
            addToDatabase.address,addToDatabase.username,addToDatabase.password,addToDatabase.contact,addToDatabase.type);
            return 1; 
        }
        return 0;
    }
};
