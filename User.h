#include <bits/stdc++.h>
#include "header.h"
#include "admin.h"

admin systemAdmin;

class User
{
    public:
    string name, surname, emailID, contact, username, password, userID, address;
    bool isBlacklisted, isLoggedIn;
    enum typeOfUser userType;

    void login();
    void signUp();
    void editProfile();
    void forgotPassword();
    void assign(profile userProfile);
    void inputPassword();

    void assign(profile userProfile)
    {
        this->name = userProfile.name;
        this->surname = userProfile.surname;
        this->emailID = userProfile.email;
        this->address = userProfile.address;
        this->username = userProfile.username;
        this->password = userProfile.password;
        this->contact = userProfile.contact;
        this->userType = userProfile.type;
        this->isBlacklisted = userProfile.isBlackListed;
        this->isLoggedIn = 1;
        this->userID = userProfile.id;
    }

    void inputPassword(profile userProfile)
    {    cout << "Enter your surname" << "\n";
            cin >> userProfile.surname;
        cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character" << "\n";
        cin >> userProfile.password;
        while (!isPasswordCorrect(userProfile.password))
        {
            cout << "Your password does not satisfy our conditions" << "\n";
            cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character" << "\n";
            cin >> userProfile.password;
        }
        cout << "Confirm your password" << "\n";
        string temp;
        cin >> temp;
        while (temp != userProfile.password)
        {
            cout << "Both passwords do not match each other" << "\n";
            inputPassword(userProfile);
        }
    }

    void login()
    {
        cout << "Enter username" << "\n";
        cin >> username;
        cout << "Enter password" << "\n";
        cin >> password;
        profile userProfile = systemAdmin.authenticate(username, password);
        if (userProfile.name == "#")
        {
            cout << "Press 1 if you forgot password" << "\n";
            cout << "Press 2 if you do not have an account" << "\n";
            cout << "Press 3 if you want to log in again" << "\n";
            int input;
            cin >> input;
            if (input == 1)
                this->forgotPassword();
            else if (input == 2)
                this->signUp();
            else
                this->login();
        }
        assign(userProfile);
    }

    void signUp()
    {
        profile userProfile;
        cin >> userProfile.address;
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
            cout << "Your contact number is invalid" << "\n";
            cin >> userProfile.contact;
        }
        cout << "Enter your email-id" << "\n";
        cin >> userProfile.email;
        while (!isEmailCorrect(userProfile.email))
        {
            cout << "Use iitj email id" << "\n";
            cin >> userProfile.email;
        }
        cout << "Your username should consist of nothing other than small letters and capital letters and numbers and underscores" << "\n";
        cout << "Enter your username" << "\n";
        cin >> userProfile.username;
        while (!isUsernameCorrect(userProfile.username))
        {
            cout << "Your username does not satisfy our conditions" << "\n";
            cout << "Your username should consist of nothing other than small letters and capital letters and numbers and underscores" << "\n";
            cin >> userProfile.username;
        }
        inputPassword(userProfile);
        cout << "Enter your address" << "\n";
        userProfile.isBlackListed = 1;
        systemAdmin.signUp(userProfile);
        assign(userProfile);
        if(this->userType==(enum typeOfUser)ShopKeeper)systemAdmin.ShopKeeperid_to_name[this->userID]= this->name;
    }

    void updateProfile()
    {
        systemAdmin.editProfile(this->userID);
    }

    void forgotPassword()
    {
    }
};



