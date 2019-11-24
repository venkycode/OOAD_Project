//#include "header.h"
#include "User.h"
#include "colormod.h"
#include <pthread.h>

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

const string clearscreen = "\033[2J";
const string cursorAdjust = "\033[1;1H";

int main()
{

    systemAdmin.loadDatabase();
    Color::Modifier bgred(Color::BG_RED);
    Color::Modifier fgred(Color::FG_RED);
    Color::Modifier fgblue(Color::FG_BLUE);
    Color::Modifier fggreen(Color::FG_GREEN);
    Color::Modifier bgblue(Color::BG_BLUE);
    Color::Modifier bgdef(Color::BG_DEFAULT);
    cout << clearscreen;
    cout << cursorAdjust;
    int choice;
    cout << "\t\t\t\t\t\t\t\t\t" << bgblue << fgred << "ONLINE DELIVERY SYSTEM " << bgdef << endl;
    cout << "\t\t\t\t\t\t\t\t\t       " << fggreen << "LOGIN[" << fgred << "1" << fggreen << "]" << endl;
    cout << "\t\t\t\t\t\t\t\t\t       " << fggreen << "SIGN UP[" << fgred << "2" << fggreen << "]" << endl;
    cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << ">>   " << fgblue;
    cin >> choice;
    if (choice == 1)
    {
        cout << clearscreen;
        cout << cursorAdjust;
        cout << "\t\t\t\t\t\t\t\t\t" << bgblue << fgred << "ONLINE DELIVERY SYSTEM " << bgdef << endl;
        cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << ">>   " << fgblue;
        string username;
        string password;
        cin >> username;
    }
}