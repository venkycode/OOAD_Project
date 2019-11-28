#include "deliveryPerson.h"
User *runTimeUserGlobal;

void customerDashboard(customer *);
void nextToMainPage(User *, int);
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
    printOption(9, 8, "EXIT ", 3);
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
    else if (choice == 3)
    {
        printHeader();
        cout << endl
             << endl
             << endl;
        cout << printtabs(9) << fgred << "Exiting ......";
        cout << endl
             << endl
             << endl;
        delayBy(3);
        logStream << ">>> !!! END OF LOG !!! <<<<<\n";
        logging.close();
        exit(0);
    }
    else if (choice == 999)
    {
        int x;
        printHeader();
        printOption(9, 0, ">>>admindash<<<<");
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
    logStream << "mainpage " << runTimeUserGlobal->userType;
    printHeader();
    cout << endl;
    cout << endl;
    printOption(9, 0, "Processing......");
    cout << endl
         << endl
         << endl;
    delayBy(2);
    nextToMainPage(runTimeUserGlobal, choice);
}

void customerDashBoard(customer *customerObject)
{
    printHeader();
    delayBy(1);
    printOption(9, 3, "Welcome ", 0);
    delayBy(1);
    cout << fgblue << customerObject->name << fggreen;
    delayBy(1.4);
    cout << " :)";
    cout << endl;
    cout << endl;
    printOption(9, 0, "SEARCH PRODUCT", 1);
    printOption(9, 0, "SHOW TOP PRODUCTS", 2);
    printOption(9, 0, "EDIT PROFILE", 3);
    printOption(9, 0, "DELETE PROFILE", 4);
    printOption(9,0,"Show WishList ",5);
    printOption(9,0,"Show Cart ",6);
    printOption(9,0,"Check Order Status ",7);
    printOption(9, 0, "Show Transactions ", 8);
    printOption(9, 0, "Show Unfinished Transactions ", 9);
    printOption(9, 3, "LOGOUT ", 10);
    printInputField();
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        customerObject->search();
        customerDashBoard(customerObject);
    }
    else if (choice == 3)
    {
        customerObject->updateProfile();
        customerDashBoard(customerObject);
    }
    else if (choice == 2)
    {
        customerObject->displayTopRatedProducts();
        customerDashBoard(customerObject);
    }
    else if (choice == 4)
    {
        if (systemAdmin.deleteID(customerObject->userID, customerObject->username))
        {
            printHeader();
            cout << endl
                 << endl
                 << endl;
            cout << printtabs(8) << fgred << "It was good having you" << endl;
            delayBy(1.6);
            mainPage();
        }
        else customerDashBoard(customerObject);
    }
    else if(choice==5)
    {
        customerObject->displayWishlist();
        customerDashBoard(customerObject);
    }
    else if(choice==6)
    {
        customerObject->displayCart();
        customerDashBoard(customerObject);
        
    }
    else if(choice==7)
    {
        customerObject->checkStatus();
        customerDashBoard(customerObject);
    }
    else if (choice == 8)
    {
        customerObject->showAllTransaction();
        customerDashBoard(customerObject);
    }
    else if(choice==9)
    {
        customerObject->displayUnfinishedOrders();
        customerDashBoard(customerObject);
    }
    else if (choice == 10)
        mainPage();
}

void shopKeeperDashBoard(shopKeeper *shopkeeperObject)
{
    printHeader();
    delayBy(0.5);
    printOption(9, 3, "Welcome ", 0);
    delayBy(0.5);
    cout << fgblue << shopkeeperObject->name;
    delayBy(1);
    cout << fggreen << " :)";
    cout << endl;
    cout << endl;
    delayBy(1);
    printOption(9, 6, "EDIT PROFILE", 1);
    printOption(9, 1, "ADD PRODUCT TO INVENTORY", 2);
    printOption(9, 0, "REMOVE PRODUCT FROM INVENTORY", 3);
    printOption(9, 1, "CHANGE PRICE OF PRODUCT", 4);
    printOption(9, 1, "CHANGE COUNT OF PRODUCT", 5);
    printOption(9, 3, "DISPLAY INVENTORY", 6);
    printOption(10, 1, "LOGOUT", 7);
    printOption(9, 5, "DELETE PROFILE", 8);
    printInputField();
    int choice;
    cin>>choice;
    switch (choice)
    {
    case 1:
        shopkeeperObject->updateProfile();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 2:
        shopkeeperObject->addToInventory();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 3:
        shopkeeperObject->removeFromInventory();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 4:
        shopkeeperObject->changePrice();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 5:
        shopkeeperObject->changeCount();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 6:
        shopkeeperObject->displayInventory();
        shopKeeperDashBoard(shopkeeperObject);
        break;
    case 7:
        mainPage();
        break;
    case 8:
        if(systemAdmin.deleteID(shopkeeperObject->userID, shopkeeperObject->username))mainPage();
        else shopKeeperDashBoard(shopkeeperObject);
    default:
        shopKeeperDashBoard(shopkeeperObject);
    }
}

void deliveryPersonDashBoard(deliverPerson *deliverPersonObject){
    printHeader();
    delayBy(0.5);
    printOption(9, 6, "ASSIGNED ORDER", 1);
    printOption(9, 6, "GET PRODUCT INFO", 2);
    printOption(9, 6, "UPDATE ORDER STATUS", 3);
    printOption(9, 6, "EDIT PROFILE", 4);
    printOption(10, 1, "LOGOUT", 5);
    printOption(9, 5, "DELETE PROFILE", 6);
    printInputField();
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
            deliverPersonObject ->checkIfOrderIsAssigned();
            deliveryPersonDashBoard(deliverPersonObject);
            break;
        case 2:
            deliverPersonObject ->getProductInfoFromId();
            deliveryPersonDashBoard(deliverPersonObject);
            break;
        case 3:
            deliverPersonObject ->updateStatus();
            deliveryPersonDashBoard(deliverPersonObject);
            break;
        case 4:
            deliverPersonObject ->updateProfile();
            deliveryPersonDashBoard(deliverPersonObject);
            break;
        case 5:
            mainPage();
            break;
        case 6:
            if (systemAdmin.deleteID(deliverPersonObject->userID, deliverPersonObject->username))
            {
                printHeader();
                cout << endl
                    << endl
                    << endl;
                cout << printtabs(8) << fgred << "It was good having you" << endl;
                delayBy(1.6);
                mainPage();
            }
            else deliveryPersonDashBoard(deliverPersonObject);
            break;
        default:
            deliveryPersonDashBoard(deliverPersonObject);
            break;
    }
}

void nextToMainPage(User *runTimeUser, int choice)
{
    logStream << "here1 " << runTimeUser->userType << " " << runTimeUser->userID << endl;
    if (runTimeUser->userID[0] == 'C')
    {
        customer *runTimeCustomer;
        runTimeCustomer = new customer(runTimeUser->finalProfile);
        logStream << "here1 " << runTimeCustomer->userType << endl;
        customerDashBoard(runTimeCustomer);
    }
    else if (runTimeUser->userID[0] == 'S')
    {
        shopKeeper *runTimeShopKeeper;
        runTimeShopKeeper = new shopKeeper(runTimeUser->finalProfile);
        logStream << "here1 " << runTimeShopKeeper->userType << endl;
        shopKeeperDashBoard(runTimeShopKeeper);
    }
    else if(runTimeUser->userID[0] == 'D'){
        deliverPerson *runTimeDeliveryPerson;
        runTimeDeliveryPerson = new deliverPerson(runTimeUser->finalProfile, choice);
        logStream << "here1 " << runTimeDeliveryPerson->userType << endl;
        deliveryPersonDashBoard(runTimeDeliveryPerson);
    }
    else mainPage();
}
