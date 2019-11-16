#include<bits/stdc++.h>
#include "header.h"
#include "admin.h"

admin systemAdmin;

class User{
    string name,surname,emailID,contact,username,password,userID,address;
    bool isBlacklisted, isLoggedin;
    enum typeOfUser userType;

    void login(){
        cout<<"Enter username" << "\n";
        cin>>username;
        cout<<"Enter password" << "\n" ;
        cin >> password ;
        profile userProfile=systemAdmin.authenticate(username,password);
        if(userProfile)
    }

}