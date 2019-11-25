//#include "header.h"
//#include "User.h"
//#include "colormod.h"
//#include <pthread.h>
#include "Customer.h"

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
        {
            delayBy(0.5);
            runTimeUser->login();
        }
        else if (choice == 2)
        {
            delayBy(0.5);
            runTimeUser-> signUp();
        }
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

void customerDashBoard(customer* customerObject)
{
    printHeader();
    delayBy(1);
    printOption(9,0,"Welcome ",0);
    cout<<fgblue<<customerObject->name<<fggreen<<" :)";
    cout<<endl;
    printOption(9,3,"");
}

int main()
{

    logStream << ">>> !!! START OF LOG !!! <<<<<\n";
    systemAdmin.setSystemState(1,1,0,0,0,0);
    systemAdmin.loadDatabase();
    cout << clearscreen;
    cout << cursorAdjust;
    mainPage();
    if(runTimeUser->userType== Customer)
    {
        customer *runTimeCustomer;
        runTimeCustomer=new customer(runTimeUser->finalProfile);
        customerDashBoard(runTimeCustomer);

    }
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    systemAdmin.dumpData();
    logStream.close();
    
}
