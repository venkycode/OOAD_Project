#include <sqlite3.h>
#include <chrono>
#include <ctime>
#include <bits/stdc++.h>
#include <unistd.h>
#include "checks.h"
#include "PasswordGenerator.h"
#include "forgotPassword.h"
#include "sha256.h"

// System state is used to store current count of shopkeepers
// delivery persons and Customers and also the current product count and also
// the current order count which helps in providing new id's
typedef struct systemState
{
    int shopKeeperCount, deliveryPersonCount, CustomerCount;
    int OrderCount, productCount;

} systemState;
systemState state;

string temporaryID;                  // also helps in adding transactions.
profile temporaryProfile;           // helps in editing profile.
string add;                        // helps in adding to the sql transactions.
order temporaryOrder;             // helps in getting info about order
vector<int> tempOrderofCustomer; // helps in retriecing the customer's order from sql.
int temporaryOrderID;           // used in assigning the order to the delivery person
class admin
{
public:
    sqlite3 *DB;            // sql database pointer.
    int exit;              // exit helps in identifying the error when performing different sql operations.
    string data;          // helps in passing certain operation while performing different sql operations.
    char *messaggeError; // helps in identifying different sql errors.

    product *global_inventory_array;          // array to load the complete data from data file.    
    map<string, set<int>> global_inven_map;   //mapping from product name to product
    fstream global_inve_file;                 // pointer for the file which stores the inventory.
    map<string, set<int>> personal_inventory; // shopkeeper id mapped to vector of productsID owned by him
    map<int, product> productId_to_product;   // map from product id to its contents.
    
    admin(){
        loadDatabase();             // loads database into local memory as soon as admin is loaded.
        assignUnassignedOrders();  //assigns uniassigned orders if possible to unassigned delivery personnel on start of code.
    }

    // callback helps in displaying the contents of user transaction from sql.
    static int callback(void *data, int argc, char **argv, char **azColName)
    {
        for (int i = 0; i < argc; i++)
            printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
        return 0;
    }

    // get_ID helps in retrieving user ID from user_map sql.
    static int get_ID(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[0] ? argv[0] : "#";
        return 0;
    }

    // get_information helps in extracting information from person sql to load locally.
    static int get_information(void *data, int argc, char **argv, char **azColName)
    {
        temporaryProfile.name = argv[1];
        temporaryProfile.surname = argv[2];
        temporaryProfile.email = argv[3];
        temporaryProfile.address = argv[4];
        temporaryProfile.contact = argv[5];
        temporaryProfile.username = argv[6];
        temporaryProfile.password = argv[7];
        return 0;
    }

    // helps in getting information from Order sql.
    static int get_info_Order(void *data, int argc, char **argv, char **azColName)
    {
        temporaryOrder.OrderID = argv[0];
        temporaryOrder.order_ = argv[1];
        temporaryOrder.customerID = argv[2];
        temporaryOrder.remainingTime = argv[3];
        temporaryOrder.other_details = argv[4];
        return 0;
    }

    // returns order details when called.
    order extactOrderInfo(string orderID){
        temporaryOrder.customerID = "#";
        string query = "SELECT * FROM ALL_ORDERS_DB WHERE ORDER_ID = \'" + orderID + "\';";
        int exit = sqlite3_exec(DB, query.c_str(), get_info_Order, NULL, NULL);
        if (exit != SQLITE_OK)
            logStream <<__func__<< "Error SELECT" << endl;
        else
        {
            logStream << "Operation OK!" << endl;
        }
        return temporaryOrder;
    }

    // helps in updating time left for a product to arrive in sql.
    void updateTime(string orderID, string remainingTime){
        string query = "UPDATE ALL_ORDERS_DB set TIME_LEFT = \'" + remainingTime + "\' WHERE ORDER_ID = \'" + orderID + '\'';
        int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        logStream<<query<<endl;
        if (exit != SQLITE_OK)
            logStream << "Error SELECT" << endl;
        else
        {
            logStream << "Operation OK!" << endl;
        }
    }

    // creats databse if it is not already present.
    void createDataBase()
    {
        int exit = 0;
        exit = sqlite3_open("userDatabase.db", &DB); //creats sql database if not already present.
        if (exit)
        {
            logStream << "Error open DB " << sqlite3_errmsg(DB) << endl; // logstream logs error if there is an issue creating table.
            std::exit(1); // exits the code if there is error.
        }
        else
            logStream << "Created Database Successfully!" << std::endl;
        string sql = "CREATE TABLE PERSON("
                     "ID TEXT PRIMARY KEY     NOT NULL, "
                     "NAME    TEXT    NOT NULL, "
                     "SURNAME   TEXT     NOT NULL, "
                     "EMAIL_ID   TEXT     NOT NULL, "
                     "ADDRESS    CHAR(50), "
                     "CONTACT_NO   TEXT  NOT NULL,"
                     "USERNAME    TEXT   NOT NULL,"
                     "PASSWORD   TEXT   NOT NULL);";
        string sql2 = "CREATE TABLE USER_TRANSACTION("
                      "ID TEXT PRIMARY KEY     NOT NULL, "
                      "TRANSACTIONS  TEXT  NOT NULL );";
        string sql3 = "CREATE TABLE USER_MAP("
                      "USERNAME TEXT PRIMARY KEY     NOT NULL, "
                      "ID  TEXT  NOT NULL );";
        string sql4 = "CREATE TABLE BLACKLISTED("
                      "USERNAME TEXT PRIMARY KEY     NOT NULL );";
        string sql5 = "CREATE TABLE ASSIGNED_ORDER("
                      "ID TEXT PRIMARY KEY     NOT NULL, "
                      "ORDER_ID  TEXT  NOT NULL );";
        string sql6 = "CREATE TABLE WISHLIST("
                      "ID TEXT PRIMARY KEY     NOT NULL, "
                      "ITEMS  TEXT  NOT NULL );";
        string sql7 = "CREATE TABLE ALL_ORDERS_DB("
                      "ORDER_ID TEXT PRIMARY KEY     NOT NULL, "
                      "ORDER_    TEXT    NOT NULL, "
                      "CUSTOMER_ID   TEXT    NOT NULL, "
                      "TIME_LEFT   TEXT    NOT NULL, "
                      "OTHER_DETAILS  TEXT  NOT NULL );";
        string sql8 = "CREATE TABLE UNASSIGNED_DELIVERY_PERSON("
                      "ID TEXT PRIMARY KEY     NOT NULL );";
        string sql9 = "CREATE TABLE UNASSIGNED_ORDERS("
                      "ORDER_ID TEXT PRIMARY KEY     NOT NULL );";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql3.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql4.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql5.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql6.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql7.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql8.c_str(), NULL, 0, &messaggeError);
        exit = sqlite3_exec(DB, sql9.c_str(), NULL, 0, &messaggeError);
        // the above commands create tables if not alredy created.
        if (exit == SQLITE_OK)
        {
            logStream << "Error Create Table" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Table created Successfully" << endl;
    }

    // helps in getting name for user when given an ID.
    static int get_name(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[1];
        return 0;
    }

    // retrieves the name of the user from the sql table using ID. 
    string nameFromId(string id)
    {
        temporaryID = "#";  // '#' is returned if id is not present in the databse.
        string query = "SELECT * FROM PERSON WHERE ID = \'" + id + "\';";
        int rc = sqlite3_exec(DB, query.c_str(), get_name, NULL, NULL);
        if (rc != SQLITE_OK)
            logStream << __func__<<"Error select"
                 << "\n";
        else
            logStream<< __func__ << "Operation OK"
                 << "\n";
        return temporaryID; // temporaryID stores the name if found in the database.
    }

    // adds unassigned order to an sql table so that it could be assigned to a delivery
    // as soon as any are free.
    void add_unassginedOrder(string orderId){
        string temp = '\'' + orderId + "\'";
        string sql("INSERT INTO UNASSIGNED_ORDERS VALUES(" + temp + ");");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        // adds the order to the database. If not possible logs an error in logStream.

        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert    " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // helps in retrieving order of users using the USERID from sql.
    static int get_Order(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[0];
        return 0;
    }

    // returns a single unassigned order if possible else returns -1.
    int get_unassignedOrder(){
        temporaryID = "-1";
        string sql("SELECT * FROM UNASSIGNED_ORDERS;");
        int rc = sqlite3_exec(DB, sql.c_str(), get_Order, NULL, NULL);
        if (rc != SQLITE_OK)
            logStream << "Error select"
                 << "\n";
        else
            logStream << "Operation OK"
                 << "\n";
        // -1 is returned if there are no unassigned orders.
        return stoi(temporaryID); // temporaryID stores an unassigned orderID.
    }

    // deletes unassigned orderid from its sql database if it is assigned to some delivery person.
    void delete_unassignedOrder(string orderId){
        string sql = "DELETE FROM UNASSIGNED_ORDERS WHERE ORDER_ID = \'" + orderId + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        // logs an error in logStream if it was not possible or the orderID was not present in the table.
        // else logs that the operation was successful.
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
    }

    // helps in retriving the address of any user from its respective sql table.
    static int get_address(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[0];
        return 0;
    }

    // returns the address of any user given its userID.
    // returns '#' if the ID is not present in the database.
    string addressFromId(string id)
    {
        temporaryID = "#";
        string query = "SELECT ADDRESS FROM PERSON WHERE ID = \'" + id + "\';";
        int rc = sqlite3_exec(DB, query.c_str(), get_address, NULL, NULL);
        if (rc != SQLITE_OK)
            logStream << "Error select"
                 << "\n";
        else
            logStream << "Operation OK"
                 << "\n";
        return temporaryID; // temporaryID contains the address if the ID is found in the database.
    }

    // loads both the databases i.e. the sql database and also the file handling database
    // into the local memory or creates them if they were already not present in the database
    // it also loads the log file and the password backdoor for read and write and also the 
    // system state into the memory and transfers all the data from the file to local memory
    // in order to process them excepting the data of sql which provides for fast search
    // and also the data of the log file and password backdoor which were not required locally
    void loadDatabase()
    {
        createDataBase();
        passwordBackdoor.open("passwordBackdoor.txt",ios::out|ios::app);
        global_inve_file.open("global_inventory_db", ios::in);

        if (!global_inve_file.is_open())
        {
            global_inve_file.open("global_inventory_db", ios::out);
            global_inve_file.close();
            global_inve_file.open("global_inventory_db", ios::in);
        }
        // loads all the inventory locally to the global inventory array.

        ifstream sysfile;
        sysfile.open("systemState", ios::in);
        sysfile.read((char *)&state, sizeof(systemState));
        sysfile.close();
        // loads the data of system state then closes the file.

        logStream<<"systemState(cus,shop,del,...) "<<state.CustomerCount<<" "<<
        state.shopKeeperCount<<" "<<state.deliveryPersonCount<<" "<<state.productCount<<\
        " "<<state.OrderCount<<endl;
        global_inve_file.seekg(0, ios::end);
        int fileSize = global_inve_file.tellg();
        logStream << fileSize << endl;
        global_inve_file.seekg(0, ios::beg);
        int size = fileSize / sizeof(product);
        global_inventory_array = (product *)malloc(size * sizeof(product));
        logStream << global_inve_file.tellg() << endl;
        global_inve_file.read((char *)global_inventory_array, fileSize);
        logStream << "size " << size << endl;
        // logs every detail in the log file for the admin

        for (int i = 0; i < size; ++i)
        {
            global_inven_map[global_inventory_array[i].product_name].insert(global_inventory_array[i].product_id);
            personal_inventory[global_inventory_array[i].shopkeeper_id].insert(global_inventory_array[i].product_id);
            productId_to_product[global_inventory_array[i].product_id] = (global_inventory_array[i]);
        }
        // loads all the data of the global inventory in different local entities.
        // then closes all the files.
        global_inve_file.close();
    }

    // Inserts a new user in the sql database i.e. userMap and also person etc.
    string Insert(string name, string surname, string email, string address, string username, string password, string contact, enum typeOfUser type)
    {
        string id = "";
        if (type == Customer)
        {
            id = 'C' + to_string(state.CustomerCount++);
        }
        else if (type == deliveryPerson)
        {
            id = 'D' + to_string(state.deliveryPersonCount++);
        }
        else
        {
            id = 'S' + to_string(state.shopKeeperCount++);
        }
        passwordBackdoor<<username<<" "<<password<<endl;
        // puts the password in the password backdoor
        password = sha256(password);
        // hashes the password so as to protect the password from theft

        string temp1 = '\'' + id + "\',\'" + name + "\',\'" + surname + "\',\'" + email + "\',\'" + address + "\',\'" + contact + "\',\'" + username + "\',\'" + password + '\'';
        string temp = '\'' + username + '\'' + ',' + '\'' + id + '\'';
        string temp2 = '\'' + id + "\',\'\'";
        string sql("INSERT INTO PERSON VALUES(" + temp1 + ");");
        string sql1("INSERT INTO USER_MAP VALUES(" + temp + ");");
        string sql2("INSERT INTO USER_TRANSACTION VALUES(" + temp2 + ");");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert    " << messaggeError << endl;
            sqlite3_free(messaggeError);
            // logs error in the log file if the insertion was not possible.
        }
        else
            logStream << "Record inserted Successfully!" << endl;

        exit = sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;

        exit = sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
        
        // finally this function returns the user's unique id to the caller.
        return id;
    }

    // checks if the username and password exist in the sql database
    // and also returns the details of the user for local use if it did exist.
    profile authenticate(string username, string password)
    {
        string query = "SELECT ID FROM USER_MAP WHERE USERNAME = \'" + username + "\';";
        int rc = sqlite3_exec(DB, query.c_str(), get_ID, NULL, NULL);
        string tmp = temporaryID;
        if (rc != SQLITE_OK || temporaryID == "#" || isBlackListed(username))
        {
            printHeader();
            cout << fgred << "\t\t\t\t\t\t\t\t\t\tINCORRECT Username or Password!!!!" << endl;
            // displays if not present in the database.
            temporaryProfile.name = "#";
            return temporaryProfile;
        }
        else
        {
            logStream << "Operation OK!" << endl;
        }
        temporaryProfile.id = tmp;
        query = "SELECT * FROM PERSON WHERE ID = \'" + tmp + "\';";
        sqlite3_exec(DB, query.c_str(), get_information, NULL, NULL);
        if (temporaryProfile.password != password)
        {
            delayBy(0);
            printHeader();
            cout << fgred << "\t\t\t\t\t\t\t\t     INCORRECT Username or Password" << endl;
            // displays incorrect password if the username was present but the password
            // did not match with the information.
            cout << endl;
            temporaryProfile.name = "#";
            return temporaryProfile;
        }
        // temporaryProfile contains the details of the user as provided by
        // the database if it existed in the database else it contains garbage 
        // values while temporaryProfile.name = '#' to identify that it did not
        // exist in the database.
        return temporaryProfile;
    }

    // deletes ID from the database completely if the user wishes
    bool deleteID(string id, string username)
    {
        // it destroys the complete data of the user from person and
        // usermap and also its transactions from user_transactions
        printHeader();
        cout<<fgred<<printtabs(9)<<"Are you sure you want to delete your account?(Y/n)"<<endl;
        cout<<fgblue<<printtabs(9)<<">>";
        string response;
        cin>>response;
        if(response!="Y"&&response!="y") return 0;
        // RETURNS 0 if the user opts to not delete his id.

        string sql = "DELETE FROM PERSON WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
        sql = "DELETE FROM USER_TRANSACTION WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from USER_TRANSACTION!" << endl;
        sql = "DELETE FROM USER_MAP WHERE USERNAME = \'" + username + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from USER_MAP!" << endl;

        // returns 1 if the id was successfully deleted from the database.
        return 1;
    }

    // changeProfile helps in editing the sql databases using the given information.
    void changeProfile(string id, string name, string surname, string email, string address, string username, string password, string contact)
    {
        string sql = "DELETE FROM PERSON WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully!" << endl;
        string temp1 = '\'' + id + "\',\'" + name + "\',\'" + surname + "\',\'" + email + "\',\'" + address + "\',\'" + contact + "\',\'" + username + "\',\'" + password + '\'';
        string sql1("INSERT INTO PERSON VALUES(" + temp1 + ");");
        exit = sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // editProfile gives option to change the profile of User.
    // it also returns the current profile
    profile editProfile(string id,profile& profileToEdit)
    {
        // This function step wise gives option to the user to edit 
        // different aspects of his profile.
        printHeader();
        char check;
        if(id[0]=='S'){
            cout <<fggreen<<printtabs(8)<< "Do you wish to change your shop name?(Y/n) :: "<<fgblue;
            cin >> check;
            if (check == 'Y' || check == 'y')
            {
                printInputField();
                string new_name;
                cin >> new_name;
                profileToEdit.name = new_name;
            }
        }
        else{
            cout <<fggreen<<printtabs(8)<< "Do you wish to change your name?(Y/n) :: "<<fgblue;
            cin >> check;
            if (check == 'Y' || check == 'y')
            {
                printInputField();
                string new_name;
                cin >> new_name;
                profileToEdit.name = new_name;
            }
            cout << fggreen<<printtabs(8)<< "Do you wish to change your Surname?(Y/n) :: "<<fgblue;
            cin >> check;
            if (check == 'Y' || check == 'y')
            {
                printInputField();
                string new_surname;
                cin >> new_surname;
                profileToEdit.surname = new_surname;
            }
        }
        cout << fggreen<<printtabs(8)<< "Do you wish to change your Email ID?(Y/n) :: "<<fgblue;
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            printInputField();
            string new_email;
            cin >> new_email;
            while (!isEmailCorrect(new_email))
            {
                cout <<fggreen<<printtabs(8)<<  "Enter a valid Email address(Only IIT Jodhpur official email addresses are considered valid) ";
                cin >> new_email;
            }
            profileToEdit.email = new_email;
        }
        cout <<fggreen<<printtabs(8)<<  "Do you wish to change your address?(Y/n) :: "<<fgblue;
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            printInputField();
            string new_address;//cin>>new_address;
            getline(cin,new_address);
            getline(cin,new_address);
            profileToEdit.address = new_address;
        }
        cout <<fggreen<<printtabs(8)<< "Do you wish to change your Contact number?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            printInputField();
            string new_contact;
            cin >> new_contact;
            while (!isContactCorrect(new_contact))
            {
                cout <<fggreen<<printtabs(8)<<  "Enter a valid contact number";
                cin >> new_contact;
            }
            profileToEdit.contact = new_contact;
        }
        cout <<fggreen<<printtabs(8)<< "Do you wish to change your Password?(Y/n) :: ";
        cin >> check;
        if (check == 'Y' || check == 'y')
        {
            printInputField();
            string new_password, confirm_new_password;
            cin >> new_password;
            cout << printtabs(8) << "Confirm Password: ";
            cin >> confirm_new_password;
            while (!(isPasswordCorrect(new_password) && confirm_new_password == new_password))
            {
                cout << "Enter a valid Password: ";
                cin >> new_password;
                cout << "Confirm Password: ";
                cin >> confirm_new_password;
            }
            // hashes the password and also stores the new password 
            // in the passwordBackdoor.
            passwordBackdoor << profileToEdit.username << ' ' << profileToEdit.password<<endl;
            profileToEdit.password = sha256(new_password);
        }
        // calls changeProfile to edit information in the database.
        changeProfile(id, profileToEdit.name, profileToEdit.surname, profileToEdit.email, profileToEdit.address, profileToEdit.username, profileToEdit.password, profileToEdit.contact);
        // returns the edited profile for local use.
        return profileToEdit;
    }

    // helps in editing the remaining delivery time in the database 
    static int update(void *data, int argc, char **argv, char **azColName)
    {
        string tmp1 = "";
        if (argv[0] != NULL)
            tmp1 = argv[0];
        string tmp = tmp1 + add;
        string sql = "UPDATE USER_TRANSACTION set TRANSACTIONS = \'" + tmp + "\' WHERE ID = \'" + temporaryID + '\'';
        temporaryID = sql;
        return 0;
    }

    // adds Transaction in the database
    void addTransaction(string id, bool isPaid, int moneyTransferred, int orderID, string payment_mode, string timeOfOrder, string paymentUsing)
    {
        string temp = "Using ";
        if (payment_mode == "CASH ON DELIVERY")
            temp = "";
        string query = "SELECT TRANSACTIONS FROM USER_TRANSACTION WHERE ID = \'" + id + "\';";
        add = to_string(orderID) + " | " + (isPaid ? "Paid" : "Refunded") + " | " + to_string(moneyTransferred) +
              " | " + payment_mode + " | " + temp + paymentUsing + " | " + timeOfOrder + "\n";
        temporaryID = id;
        sqlite3_exec(DB, query.c_str(), update, NULL, NULL);
        exit = sqlite3_exec(DB, temporaryID.c_str(), callback, NULL, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "SQL error: " << messaggeError <<endl;
            sqlite3_free(messaggeError);
            // logs error in the log file if it was not possible to add the transaction
        }
        else
        {
            logStream<< "Operation done successfully\n";
        }
    }

    // helps in retrieving the data of transaction from the database.
    static int get_transaction(void *data, int argc, char **argv, char **azColName)
    {
        // the information is pushed in vector named tempOrderofCustomer
        tempOrderofCustomer.clear();
        int len = strlen(argv[0]);
        bool fl = 1;
        string temp="";
        for(int i=0; i<len; ++i){
            if(argv[0][i] == '\n'){
                fl=1;
                continue;
            }
            if(argv[0][i] == ' ' && fl){
                fl=0;
                tempOrderofCustomer.push_back(stoi(temp));
                temp = "";
            }
            if(fl){
                temp+=argv[0][i];
            }
        }
        return 0;
    }

    // returns vector of the orderd product of any user.
    vector<int> orderIdsofCustomer(string id){
        string query = "SELECT TRANSACTIONS FROM USER_TRANSACTION WHERE ID = \'" + id + "\';";
        int exit = sqlite3_exec(DB, query.c_str(), get_transaction, NULL, NULL);
        if (exit != SQLITE_OK)
            logStream << "Error SELECT" << endl;
        else
        {
            logStream << "Operation OK!" << endl;
        }
        return tempOrderofCustomer;
    }

    // It displays all the transactions of any user given the userID.
    void showTransaction(string id)
    {
        string query = "SELECT TRANSACTIONS FROM USER_TRANSACTION WHERE ID = \'" + id + "\';";
        int exit = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        if (exit != SQLITE_OK)
            logStream << "Error SELECT" << endl;
        else
        {
            logStream << "Operation OK!" << endl;
        }
    }

    // finds the username from the sql database.
    static int check_username(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[0];
        return 0;
    }

    // checks if the username had been already taken in the database.
    // as we need a unique username for different personnel.
    // returns 1 if the username had been taken else returns 0.
    bool isUsernameTaken(string username)
    {
        temporaryID = "#";
        string query = "SELECT * FROM USER_MAP WHERE USERNAME = \'" + username + "\';";
        sqlite3_exec(DB, query.c_str(), check_username, NULL, NULL); // only checks if username is taken or not i.e. returns 0 only if it is taken
        if (temporaryID != "#")
            return 1;
        else
            return 0;
    }

    // Inserts new entity into the database.
    string signUp(profile addToDatabase)
    {
       return Insert(addToDatabase.name, addToDatabase.surname, addToDatabase.email,
                      addToDatabase.address, addToDatabase.username, addToDatabase.password, addToDatabase.contact, addToDatabase.type);
    }

    // function for the admin of the application.
    // helps in adding people as blacklisted if the abuse the system.
    void addToBlacklist(string username)
    {
        string sql("INSERT INTO BLACKLISTED VALUES(\'" + username + "\');");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // checks if the user is blacklisted or is good to go
    // returns 1 if blacklisted else 0.
    bool isBlackListed(string username)
    {
        temporaryID = "#";
        string query = "SELECT * FROM BLACKLISTED WHERE USERNAME = \'" + username + "\';";
        exit = sqlite3_exec(DB, query.c_str(), check_username, NULL, NULL);
        return temporaryID != "#";
    }

    // inserts new product in the inventory
    void insertProduct(product productToInsert)
    {
        productId_to_product[productToInsert.product_id] = productToInsert;
    }
    
    // sends the new password email to the user's registered 
    // email id if the username exists in the database.
    // and also edits the profile in the database.
    void forgotPassword(string username)
    {
        string new_password = PasswordGenerator();
        string message = "Your new Password is : " + new_password;
        string query = "SELECT ID FROM USER_MAP WHERE USERNAME = \'" + username + "\';";
        sqlite3_exec(DB, query.c_str(), get_ID, NULL, NULL);
        query = "SELECT * FROM PERSON WHERE ID = \'" + temporaryID + "\';";
        sqlite3_exec(DB, query.c_str(), get_information, NULL, NULL);
        temporaryProfile.password = new_password;
        sendPasswordToEmail(temporaryProfile.email, new_password);
        new_password=sha256(new_password);
        changeProfile(temporaryID, temporaryProfile.name, temporaryProfile.surname,
                      temporaryProfile.email, temporaryProfile.address, temporaryProfile.username, temporaryProfile.password, temporaryProfile.contact);
    }

    // assigns order to delivery person and also adds the information
    // in the database.
    void assign_order(string id, int orderID)
    {
        string temp = '\'' + id + "\',\'" + to_string(orderID) + '\'';
        string sql("INSERT INTO ASSIGNED_ORDER VALUES(" + temp + ");");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert    " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // removes the assigned order from a delivery Person if the order has 
    // reached its desired destination and also edits the sql database.
    void finish_order(string id)
    {
        string sql = "DELETE FROM ASSIGNED_ORDER WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
    }

    // checks if a delivery Person is available or not.
    static int check_avail(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[1];
        return 0;
    }

    // returns the assigned order ID of the delivery person in question 
    // if none were assigned it returns -1.
    int AssignedOrderId(string id)
    {
        temporaryID = "-1";
        string query = "SELECT * FROM ASSIGNED_ORDER WHERE ID = \'" + id + "\';";
        sqlite3_exec(DB, query.c_str(), check_avail, NULL, NULL);
        return stoi(temporaryID);
    }

    // helps in getting the wishlist information from the sql database.
    static int get_wishList(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[1];
        return 0;
    }

    // deleteWishlist deletes the wishlist of the user in qustion from the database.
    void deleteWishList(string id)
    {
        string sql = "DELETE FROM WISHLIST WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
    }

    // insert wishlist of some user with its information.
    void insertWishList(string id, string wishlist)
    {
        string temp = '\'' + id + "\',\'" + wishlist + '\'';
        string sql("INSERT INTO WISHLIST VALUES(" + temp + ");");
        ;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert    " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // appends to the wishlist of some user.
    void addToWishList(string id, string name)
    {
        temporaryID = "";
        string query = "SELECT * FROM WISHLIST WHERE ID = \'" + id + "\';";
        sqlite3_exec(DB, query.c_str(), get_wishList, NULL, NULL);
        if (temporaryID.size() != 0)
            deleteWishList(id);
        temporaryID += "#" + name;
        insertWishList(id, temporaryID);
    }

    // return the wishlist of a user in the form of a set of strings
    set<string> returnWishlist(string id)
    {
        temporaryID = "";
        string query = "SELECT * FROM WISHLIST WHERE ID = \'" + id + "\';";
        sqlite3_exec(DB, query.c_str(), get_wishList, NULL, NULL);
        string tmp = "";
        set<string> wishlist;
        for (auto i : temporaryID)
        {
            if (i != '#')
                tmp += i;
            else
                wishlist.insert(tmp), tmp = "";
        }
        if (tmp.size() != 0)
            wishlist.insert(tmp);
        return wishlist;
    }

    // helps in editing the wishlist of a user
    void changeWishList(string id, set<string> new_wishlist)
    {
        deleteWishList(id);
        for (auto i : new_wishlist)
        {
            addToWishList(id, i);
        }
    }

    // helps in retrieving the time left for some order to reach its
    // desired location from the sql database.
    static int get_Status(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = "";
        for(int i=0;i<8;++i)temporaryID.push_back(argv[3][i]);
        return 0;
    }

    // returns the time left in the form of a string in the 
    // format (days:hours:minutes).
    // it returns (??:??:??) if the delivery person has not yet updated the time remaining.
    string get_orderStatus(string id){
        temporaryID = "#";
        string query = "SELECT * FROM ALL_ORDERS_DB WHERE ORDER_ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, query.c_str(), get_Status, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Operation   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Operation done Successfully!" << endl;
        return temporaryID;
    }

    // insert the details of the order in the sql database.
    void insertOrder(string id, vector<pair<int,int>> curOrder, string payementUsing, string payementMode, string curTime, string customerId, string time_remaining){
        string product_ids = "",tempOrder="";
        for(auto i: curOrder){
            product_ids += "[" "Product ID : "+ to_string(i.first) + " | " + "Quantity Ordered : "+to_string(i.second) + "] ";
        }
        tempOrder += "[" + payementMode +"] ";
        if(payementUsing.length())tempOrder += "["+payementUsing+"] ";
        tempOrder += "["+curTime+"]";
        string temp = '\'' + id + "\',\'" + product_ids + "\',\'" + customerId + "\',\'" + time_remaining + "\',\'" + tempOrder + '\'';
        string sql("INSERT INTO ALL_ORDERS_DB VALUES(" + temp + ");");;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert    " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // deletes the Order from the desired sql database table
    // when the order is completed
    void deleteOrder(string id){
        string sql = "DELETE FROM ALL_ORDERS_DB WHERE ORDER_ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
    }

    // it finds an unassigned delivery person so as to assign him some order.
    static int findUnassigned(void *data, int argc, char **argv, char **azColName)
    {
        temporaryID = argv[0];
        return 0;
    }

    // returns the id of the unassigned delivery person from the database
    // if not possible returns '#'
    string find_unassigned_deliveryPerson()
    {
        temporaryID = "#";
        string sql("SELECT * FROM UNASSIGNED_DELIVERY_PERSON;");
        exit = sqlite3_exec(DB, sql.c_str(), findUnassigned, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
        return temporaryID; // It is '#' if everyone is assigned.
    }

    // deletes delivery person from the database table of unassigned delivery person
    // if he has been alloted an order.
    void delete_unassigned_deliveryPerson(string id)
    {
        string sql = "DELETE FROM UNASSIGNED_DELIVERY_PERSON WHERE ID = \'" + id + "\';";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error DELETE" << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record deleted Successfully from PERSON!" << endl;
    }

    // Adds new entry to the sql database of unassigned delivery persons
    void insert_unassigned_deliveryPerson(string id)
    {
        string sql("INSERT INTO UNASSIGNED_DELIVERY_PERSON VALUES(\'" + id + "\');");
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
        if (exit != SQLITE_OK)
        {
            logStream << "Error Insert   " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }
        else
            logStream << "Record inserted Successfully!" << endl;
    }

    // Assigns orders in waiting, if any to the available delivery persons, if any
    void assignUnassignedOrders(){
        while(1){
            string tempDeliveryPerson = find_unassigned_deliveryPerson(); // finds available delivery person, if any
            int tempOrderId = get_unassignedOrder();
            if(tempDeliveryPerson == "#" || tempOrderId == -1)break;
            delete_unassigned_deliveryPerson(tempDeliveryPerson); /* deletes that delivery person from database
                                                                     of available delivery persons */
            delete_unassignedOrder(to_string(tempOrderId)); /* deletes the corresponding order from the sql database 
                                                                of orders in waiting */
            assign_order(tempDeliveryPerson, tempOrderId);
        }
    }

    // A function which takes care of entire payment procedure
    void payment(vector<pair<product, int>> Cart, enum mode payment_mode, string contact, string id)
    {
        printHeader();
        cout<<endl;
        auto current_clock = chrono::system_clock::now();
        time_t cur_time = std::chrono::system_clock::to_time_t(current_clock);
        string currentTime = ctime(&cur_time); // Gives the real time of transaction
        string tempMode = "";
        int totalCost = 0;
        for (auto currentProduct : Cart)
        {
            productId_to_product[currentProduct.first.product_id].rating++;
            productId_to_product[currentProduct.first.product_id].count -= currentProduct.second;
            totalCost += (currentProduct.first.price + currentProduct.first.deliveryCharge) * currentProduct.second;
        }
        cout<<printtabs(8)<<fggreen << "Total Cost =  " << totalCost << endl;
        string cardNumber, expiry_Date, Cvv, paymentUsing = "";
        char choice;
        switch (payment_mode)
        {
        case cashOnDelivery:
            tempMode = "CASH ON DELIVERY";
            break;
        case onlineBanking:
            cout<<printtabs(8)<<fggreen << "Enter card number (****-****-****-****)" << endl;
            do
            {
                cin >> cardNumber;
            } while (!isCorrectCardNumber(cardNumber));
            paymentUsing = cardNumber;
            cout <<printtabs(8)<<fggreen<< "Enter Expiry Date (mm/yy)" << endl;
            do
            {
                cin >> expiry_Date;
            } while (!isCorrectDate(expiry_Date));
            cout<<printtabs(8)<<fggreen << "Enter Cvv (***)" << endl;
            do
            {
                cin >> Cvv;
            } while (isCorrectCvv(Cvv));
            tempMode = "ONLINE BANKING";
            break;
        case Paytm:
            cout<<printtabs(8)<<fggreen << "Do you wish to use your current number(Y/n): " << contact << endl;

            cin >> choice;
            if (!(choice == 'Y' || choice == 'y'))
            {
                do
                {
                    cin >> contact;
                } while (isContactCorrect(contact));
            }
            paymentUsing = contact;
            tempMode = "PAYTM";
            break;
        case GooglePay:
            cout<<printtabs(8)<<fggreen << "Do you wish to use your current number(Y/n): " << contact << endl;

            cin >> choice;
            if (!(choice == 'Y' || choice == 'y'))
            {
                do
                {
                    cin >> contact;
                } while (isContactCorrect(contact));
            }
            paymentUsing = contact;
            tempMode = "GOOGLE PAY";
            break;
        default:
            logStream << "No such banking option" << endl;
            break;
        }
        int orderID1 = state.OrderCount++; // Assigns ID to the order
        cout<<printtabs(8)<<fggreen << id << " " << orderID1 << " " << tempMode << " " << paymentUsing << endl;
        addTransaction(id, 1, totalCost, orderID1, tempMode, currentTime, paymentUsing); //Adds to the user transaction database
        string deliveryPersonID=find_unassigned_deliveryPerson(); // finds available delivery person, if any
        vector<pair<int,int>>tempOrder;
        for(auto y:Cart)tempOrder.push_back({y.first.product_id, y.second});
        insertOrder(to_string(orderID1),tempOrder, paymentUsing,tempMode,currentTime, id,"????????");
               // inserts order to the sql database of all orders
        if(deliveryPersonID=="#"){ // i.e. no delivery person is available
            add_unassginedOrder(to_string(orderID1)); // adds the order to the database of unassigned orders
        }
        else{
            assign_order(deliveryPersonID, orderID1); // Assigns order to the given delivery person
            delete_unassigned_deliveryPerson(deliveryPersonID); /* deletes the corresponding delivery person from the database
                                                                    of available delivery persons */
        }

    }

    // Adds the product to shopkeeper's personal inventory
    void addToInventory(product productToAdd)
    {
        personal_inventory[productToAdd.shopkeeper_id].insert(productToAdd.product_id);
        productId_to_product[productToAdd.product_id] = productToAdd;
        global_inven_map[productToAdd.product_name].insert(productToAdd.product_id);
    }

    // Changes the quantity of products in shopkeeper's personal inventory
    void changeProductCount(int productID, int changedCount)
    {
        productId_to_product[productID].count = changedCount;
    }

    // Changes the price of products in shopkeeper's personal inventory
    void changeProductPrice(int productID, int changedPrice)
    {
        productId_to_product[productID].price = changedPrice;
    }

    // debugging function
    void setSystemState(int cusCnt, int shpCnt, int delCnt, int prodCnt, int OrdCnt)
    {
        remove("systemState");
        fstream file;
        file.open("systemState", ios::out);
        systemState madeUpState;
        madeUpState.CustomerCount = cusCnt;
        madeUpState.shopKeeperCount = shpCnt;
        madeUpState.deliveryPersonCount = delCnt;
        madeUpState.OrderCount = OrdCnt;
        madeUpState.productCount = prodCnt;
        file.write((char *)&madeUpState, sizeof(systemState));
        file.close();
    }

    // A class destructor which dumps new data into corresponding files
    ~admin()
    {
        global_inventory_array = (product *)malloc(productId_to_product.size() * sizeof(product));
        int index = 0;
        for (auto i : productId_to_product)
        {
            global_inventory_array[index] = i.second;
            index++;
        }
        remove("global_inventory_db");
        global_inve_file.open("global_inventory_db", ios::out);
        global_inve_file.write((char *)global_inventory_array, productId_to_product.size() * sizeof(product));
        global_inve_file.close();
        remove("systemState");
        fstream outSysState;
        outSysState.open("systemState", ios::out);
        outSysState.write((char *)&state, sizeof(systemState));
        outSysState.close();
    }
};