//#include "header.h"
#include "User.h"

/*int main(){
    User temp ;
    cout<<"Press 1 to login if you already have an account" << "else press 2 to sign up" << "\n";
    cout<<"Press 3 if you forgot your password" << "\n";
    int input;cin>>input;
    if(input==1) temp.login();
    else if(input==2) temp.signUp();
    else temp.forgotPassword();
    if(!temp.isLoggedIn) return 0 ;
    cout << "Press 1 if you wish to update your profile, else press 0" << "\n";
    cin >> input ;
    if(input)temp.updateProfile();
    if(temp.userType==Customer){
        customer temp2 ;
        temp2.search();
        
    }
    else if(temp.userType==ShopKeeper){

    }
    else{
        
    }
}*/

int main(){

    User u;
    systemAdmin.loadDatabase();
    u.signUp();
    
}