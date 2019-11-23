#include <bits/stdc++.h>
#include "admin.h"

admin systemAdmin;

class User
{
    public:
    string name, surname, emailID, contact, username, password, userID, address;
    bool isLoggedIn;
    enum typeOfUser userType;


    void assignUserProfile(profile &userProfile)
    {
        name = userProfile.name;
        surname = userProfile.surname;
        emailID = userProfile.email;
        address = userProfile.address;
        username = userProfile.username;
        password = userProfile.password;
        contact = userProfile.contact;
        userType = userProfile.type;
        isLoggedIn = 1;
        userID = userProfile.id;
    }

    void inputPassword(profile &userProfile)
    {    
        string temp;
        do{
            getline(cin, userProfile.password);
            while (!isPasswordCorrect(userProfile.password))
            {
                cout << "Your password does not satisfy our conditions" << "\n";
                cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character" << "\n";
                cout << "Try again" << "\n" ;
                getline(cin, userProfile.password);
            }
            cout << "Confirm your password" << "\n";
            getline(cin,temp);
            if (temp != userProfile.password)
            {
                cout << "Both passwords do not match each other" << "\n";
                cout << "Try again" << "\n" ;
            }
        }while(temp != userProfile.password);
    }

    void login()
    {
        cout << "Enter username" << "\n";
        getline(cin,username);
        cout << "Enter password" << "\n";
        getline(cin ,password);
        profile userProfile = systemAdmin.authenticate(username, password);
        if (userProfile.name == "#")
        {
            cout << "Press 1 if you forgot password" << "\n";
            cout << "Press 2 if you do not have an account" << "\n";
            cout << "Press 3 if you want to log in again" << "\n";
            int input;
            cin >> input;
            if (input == 1)
                forgotPassword();
            else if (input == 2)
                signUp();
            else
                login();
        }
        assignUserProfile(userProfile);
    }

    void signUp()
    {
        profile userProfile;
        cout << "Press 1 if you are a customer" << "\n";
        cout << "Press 2 if you are a shopkeeper" << "\n";
        cout << "Press 3 if you are a delivery person" << "\n";
        int input;
        cin >> input;
        if (input == 1) userProfile.type = (enum typeOfUser)Customer;
        else if (input == 2) userProfile.type = (enum typeOfUser)ShopKeeper;
        else userProfile.type = (enum typeOfUser)deliveryPerson;
        if(userProfile.type == (enum typeOfUser)ShopKeeper){ 
            cout << "Enter your shop name" << "\n" ;
            cin>>userProfile.name;
            userProfile.surname="#";
        }
        else{
            cout << "Enter your name" << "\n";
            cin >> userProfile.name;
            cout << "Enter your surname" << "\n";
            cin >> userProfile.surname;
        }
        cout << "Enter your contact number" << "\n";
        cin >> userProfile.contact;
        while (!isContactCorrect(userProfile.contact))
        {
            cout << "Your contact number is invalid. Try again" << "\n";
            cin >> userProfile.contact;
        }
        cout << "Enter your email-id" << "\n";
        getline(cin, userProfile.email);
        getline(cin, userProfile.email);
        while (!isEmailCorrect(userProfile.email))
        {
            cout << "Use iitj email id" << "\n";
            getline(cin, userProfile.email);
        }
        cout << "Your username should consist of nothing other than small letters and capital letters and numbers and underscores" << "\n";
        cout << "Enter your username" << "\n";
        getline(cin, userProfile.username);
        while (!isUsernameCorrect(userProfile.username))
        {
            cout << "Your username does not satisfy our conditions" << "\n";
            cout << "Your username should consist of nothing other than small letters and capital letters and numbers and underscores" << "\n";
            cout << "Try again" << "\n" ;
            getline(cin, userProfile.username);
        }
        cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character" << "\n";
        cout << "Enter password" << "\n" ;
        inputPassword(userProfile);
        cout << "Enter your address" << "\n";
        getline(cin , userProfile.address);
        systemAdmin.signUp(userProfile);
        assignUserProfile(userProfile);
        //if(this->userType==(enum typeOfUser)ShopKeeper)systemAdmin.ShopKeeperid_to_name[this->userID]= this->name;
    }

    void updateProfile()
    {
        systemAdmin.editProfile(userID);
    }

    void forgotPassword()
    {
    }
};


