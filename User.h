#include<bits/stdc++.h>
#include "header.h"
#include "admin.h"

admin systemAdmin;

class User{
    string name,surname,emailID,contact,username,password,userID,address;
    bool isBlacklisted, isLoggedin;
    enum typeOfUser userType;

    void login();
    void signUp();
    void editProfile();
    void forgotPassword();

    void login(){
        cout<<"Enter username" << "\n";
        cin>>username;
        cout<<"Enter password" << "\n" ;
        cin >> password ;
        profile UserProfile=systemAdmin.authenticate(username,password);
        if(UserProfile.name=="#"){
            cout<<"Press 1 if you forgot password" << "\n" ;
            cout << "Press 2 if you do not have an account"<<"\n";
            cout << "Press 3 if you want to log in again" << "\n" ;
            int input;cin>>input;
            if(input==1)
        }
    }

}