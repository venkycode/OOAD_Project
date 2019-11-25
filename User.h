//#include<termios.h>
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
        do
        {
            getline(cin, userProfile.password);
            while (!isPasswordCorrect(userProfile.password))
            {
                cout << "Your password does not satisfy our conditions"
                     << "\n";
                cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character"
                     << "\n";
                cout << "Try again"
                     << "\n";
                getline(cin, userProfile.password);
            }
            cout << "Confirm your password"
                 << "\n";
            getline(cin, temp);
            if (temp != userProfile.password)
            {
                cout << "Both passwords do not match each other"
                     << "\n";
                cout << "Try again"
                     << "\n";
            }
        } while (temp != userProfile.password);
    }

    void login()
    {
        printHeader();
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << "Username" << fgblue << ">>" << fgred;
        //getline(cin,username);
        cin >> username;
        cout << endl;
        cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << "Password" << fgblue << ">>" << fgred;
        //cin>>password;
        char *tmpPass;
        tmpPass = getpass("");
        //int szar = sizeof(tmpPass) / sizeof(char);
        //logStream<<""szar<<endl;
        password = tmpPass; //convertToString(tmpPass,szar);
        logStream << "password = " << password << endl;
        logStream.flush();
        cout << endl;
        profile userProfile = systemAdmin.authenticate(username, password);
        
        if (userProfile.name == "#")
        {
            //printHeader();
            cout << fggreen << "\t\t\t\t\t\tForgot Password[" << fgred << "1" << fggreen << "]";
            cout << fggreen << "\tCreate New Account[" << fgred << "2" << fggreen << "]";
            cout << fggreen << "\tLogin[" << fgred << "3" << fggreen << "]" << endl;
            printInputField();

            int input;
            cin >> input;
            if (input == 1)
                forgotPassword();
            else if (input == 2)
                signUp();
            else
            {
                //getline(cin,username);
                login();
            }
        }
        assignUserProfile(userProfile);
    }

    void signUp()
    {
        profile userProfile;
        printHeader();
        cout << printtabs(9) << fgblue << ">> Create account as <<";
        cout << endl;
        cout << endl;
        printOption(9, 6, "Customer", 1);
        printOption(9, 5, "ShopKeeper", 2);
        printOption(9, 3, "Delivery-Person", 3);
        printInputField();
        int input;
        cin >> input;
        if (input == 1)
            userProfile.type = (enum typeOfUser)Customer;
        else if (input == 2)
            userProfile.type = (enum typeOfUser)ShopKeeper;
        else
            userProfile.type = (enum typeOfUser)deliveryPerson;
        if (userProfile.type == (enum typeOfUser)ShopKeeper)
        {
            //cout << "Enter your shop name" << "\n" ;
            printHeader();
            printOption(9, 0);
            cout << fgblue << ">> ShopKeeper Sign UP <<";
            cout << endl;
            cout << endl;
            printOption(9, 6, "ShopName", 0);
            cout << fgblue << ">>";
            cin >> userProfile.name;
            userProfile.surname = "#";
        }
        else
        {
            printHeader();
            printOption(9, 0);
            if (userProfile.type == (enum typeOfUser)Customer)
                cout << fgblue << ">> Customer  Sign  UP <<";
            else
                cout << fgblue << ">> Delivery-Person Sign UP <<";
            cout << endl;
            cout << endl;
            printOption(9, 6, "Name ", 0);
            cout << fgblue << ">>";
            cin >> userProfile.name;
            cout << endl;
            printOption(9, 4, "Surname ", 0);
            cout << fgblue << ">>";
            cin >> userProfile.surname;
            cout << endl;
            // cout << "Enter your name"
            //      << "\n";
            // cin >> userProfile.name;
            // cout << "Enter your surname"
            //      << "\n";
            // cin >> userProfile.surname;
        }
        int triedYet=0;
        do
        {
            //cout<<endl;
            printOption(9, 2, "Contact Number ", 0);
            cout << fgblue << ">>";
            cin >> userProfile.contact;

        } while (!isContactCorrect(userProfile.contact,&triedYet));

        cout << endl;
        // cout << "Enter your contact number"
        //      << "\n";
        // cin >> userProfile.contact;
        while (!isContactCorrect(userProfile.contact))
        {
            cout << "Your contact number is invalid. Try again"
                 << "\n";
            cin >> userProfile.contact;
        }
        cout << "Enter your email-id"
             << "\n";
        getline(cin, userProfile.email);
        getline(cin, userProfile.email);
        while (!isEmailCorrect(userProfile.email))
        {
            cout << "Use iitj email id"
                 << "\n";
            getline(cin, userProfile.email);
        }
        cout << "Your username should consist of nothing other than small letters and capital letters and numbers and underscores"
             << "\n";
        cout << "Enter your username"
             << "\n";
        getline(cin, userProfile.username);
        while (!isUsernameCorrect(userProfile.username) || systemAdmin.isUsernameTaken(userProfile.username))
        {
            if (!isUsernameCorrect(userProfile.username))
                cout << "Your username does not satisfy our conditions"
                     << "\n";
            else
                cout << "This username is taken"
                     << "\n";
            cout << "Try again"
                 << "\n";
            getline(cin, userProfile.username);
        }
        cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character"
             << "\n";
        cout << "Enter password"
             << "\n";
        inputPassword(userProfile);
        cout << "Enter your address"
             << "\n";
        getline(cin, userProfile.address);
        systemAdmin.signUp(userProfile);
    }

    void updateProfile()
    {
        systemAdmin.editProfile(userID);
    }

    void forgotPassword()
    {
        cout << printtabs(8) << fggreen << "Enter Username " << fgblue << ">>";
        cin >> username;
        if (systemAdmin.isBlackListed(username))
            cout << printtabs(8) << "You are blacklisted"
                 << "\n";
        else if (!systemAdmin.isUsernameTaken(username))
            cout << printtabs(8) << "This username does not exist"
                 << "\n";
        else;
            //systemAdmin.forgotPassword(username);
    }
};
