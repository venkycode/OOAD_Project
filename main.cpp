//#include "header.h"
//#include "User.h"
//#include "colormod.h"
//#include <pthread.h>
#include "Customer.h"

User *runTimeUserGlobal;

void customerDashboard(customer *);
void nextToMainPage(User *);
void mainPage();
void mainPage()
{
    int choice;
    runTimeUserGlobal = new User;
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
        runTimeUserGlobal->login();
    }
    else if (choice == 2)
    {
        delayBy(0.5);
        runTimeUserGlobal->signUp();
    }
    else
    {
        cout << printtabs(9) << fgred << "Invalid Choice...!!" << endl;
        delayBy(1);
        cout << endl;
        cout << printtabs(9) << fggreen << "Redirecting to Main Page..." << endl;
        delayBy(3);
        mainPage();
    }
    logStream<<"mainpage "<<runTimeUserGlobal->userType;
    nextToMainPage(runTimeUserGlobal);
}

void customerDashBoard(customer *customerObject)
{
    printHeader();
    delayBy(1);
    printOption(9, 3, "Welcome ", 0);
    cout << fgblue << customerObject->name << fggreen << " :)";
    cout << endl;
    cout << endl;
    printOption(9, 0, "SEARCH PRODUCT", 1);
    printOption(9, 0, "EDIT PROFILE", 2);
    printOption(9, 0, "SHOW TOP PRODUCTS",3);
    printOption(9, 0, "DELETE PROFILE",4);
    printOption(9,0,"Show Transactions",5);
    printOption(9,3,"LOGOUT",4);
    printInputField();
    int choice;
    cin>>choice;
    if(choice==1)
    {
        customerObject->search();
        customerDashBoard(customerObject);
    }
}

void nextToMainPage(User *runTimeUser)
{
    logStream<<"here1 "<<runTimeUser->userType<<" "<<runTimeUser->userID<< endl;
    if (runTimeUser->userID[0] == 'C')
    {
        customer *runTimeCustomer;
        runTimeCustomer = new customer(runTimeUser->finalProfile);
        logStream<<"here1 "<<runTimeCustomer->userType<<endl; 
        customerDashBoard(runTimeCustomer);
    }
}

int main()
{

    logStream << ">>> !!! START OF LOG !!! <<<<<\n";
    //systemAdmin.setSystemState(1, 1, 0, 0, 0);
    //systemAdmin.loadDatabase();
    cout << clearscreen;
    cout << cursorAdjust;
    mainPage();
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    logStream.close();
}
