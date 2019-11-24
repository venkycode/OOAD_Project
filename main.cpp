//#include "header.h"
//#include "User.h"
//#include "colormod.h"
//#include <pthread.h>
#include "Customer.h"

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
User* runTimeUser;
void mainPage()
    {
        int choice;
        runTimeUser=new User;
        printHeader();
        cout << "\t\t\t\t\t\t\t\t\t       " << fggreen << "LOGIN[" << fgred << "1" << fggreen << "]" << endl;
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t       " << fggreen << "SIGN UP[" << fgred << "2" << fggreen << "]" << endl;
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << ">>   " << fgblue;
        cin >> choice;
        if (choice == 1)
            runTimeUser->login();
        else if (choice == 2)
            runTimeUser-> signUp();
        else
        {
            cout << printtabs(9) << fgred << "Invalid Choice...!!" << endl;
            delayBy(1);
            cout<<endl;
            cout << printtabs(9) << fggreen << "Redirecting to Main Page..." << endl;
            delayBy(3);
            mainPage();
        }
}
int main()
{

    logStream << ">>> !!! START OF LOG !!! <<<<<\n";
    systemAdmin.setSystemState(0,1,0,0,0);
    systemAdmin.loadDatabase();
    cout << clearscreen;
    cout << cursorAdjust;
    mainPage();
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    systemAdmin.dumpData();
    logStream.close();
    
}
