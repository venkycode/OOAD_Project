#include <bits/stdc++.h>
using namespace std;

enum typeOfUser
{
    Customer,
    deliveryPerson,
    ShopKeeper
};

enum mode
{
    cashOnDelivery,
    onlineBanking,
    Paytm,
    GooglePay
};

typedef struct time
{
    int days, hours, minutes;
} time;

typedef struct product
{

} product;

typedef struct order
{
    enum mode paymentMode;
    int customerID;
    int orderID;
    bool isPlaced;
} order;

class admin
{
public:
    int cnt_shopKeeper = 0, cnt_deliveryPerson = 0, cnt_Customer = 0;
    string emailID;
    vector<order> allTransactions;
    map<string, User> userDatabase;

    bool authenticate(string username, string password)
    {
        if (userDatabase.find(username) != userDatabase.end())
        {
            return userDatabase[username].password == password;
        }
        return false;
    }
    void assign(int &userID, string &emailID, bool &isBlacklisted, enum typeOfUser &usertype, string username)
    {
        User temp = userDatabase[username];
        userID = temp.userID;
        emailID = temp.emailID;
        isBlacklisted = temp.isBlacklisted;
        usertype = temp.userType;
    }
    void forgotPassword(string username)
    {
        if (userDatabase.find(username) != userDatabase.end())
        {
        }
        else
        {
            cout << "Username not found:: " << endl;
        }
    }
};
admin systemAdmin;

class User
{
    string username;

public:
    int userID;
    string password, emailID, name;
    bool isLoggedIn, isBlacklisted;
    enum typeOfUser userType;

    void login()
    {
        cout << "Enter UserName:: ";
        cin >> username;
        cout << "Enter Password:: ";
        cin >> password;
        bool shouldAuthenticate = systemAdmin.authenticate(username, password);
        if (shouldAuthenticate == true)
        {
            systemAdmin.assign(userID, emailID, isBlacklisted, userType, username);
            if (isBlacklisted == true)
            {
                cout << "Tum Blacklisted hoe " << endl;
            }
        }
        else
        {
            cout << "Username or Password not found." << endl;
            cout << "Forgot Password (\"Y,n\") :: ";
            char check;
            cin >> check;
            if (check == 'Y')
            {
                forgotPassword();
            }
            else
                login();
        }
    }
    void signUp()
    {
        cout << "Enter name";
        cin >> name;
        cout << "Enter email";
        cin >> emailID;
        cout << "Press 0 if you are a Customer\nPress 1 if you are a ShopKeeper\nPress 2 if you are a deliveryPerson\n";
        int input;
        cin >> input;
        if (input == 0)
            userType = Customer, userID = ++systemAdmin.cnt_Customer;
        else if (input == 1)
            userType = ShopKeeper, userID = ++systemAdmin.cnt_shopKeeper;
        else
            userType = deliveryPerson, userID = ++systemAdmin.cnt_deliveryPerson;
        cout << "Enter UserName:: ";
        cin >> username;
        cout << "Enter Password:: ";
        cin >> password;
        isLoggedIn = 1;
        isBlacklisted = 0;
        systemAdmin.userDatabase[username] = this;
    }
    void updateProfile()
    {
        cout << "Press 1 if you have to change name\n";
    }
    void forgotPassword()
    {
        cout << "Enter Username :: ";
        cin >> username;
        systemAdmin.forgotPassword(username);
    }
};
