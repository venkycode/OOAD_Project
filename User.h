//#include<termios.h>
#include "admin.h"
admin systemAdmin;

class User
{
public:
    string name, surname, emailID, contact, username, password, userID, address;
    enum typeOfUser userType;
    profile finalProfile;


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
        userID = userProfile.id;
        finalProfile=userProfile;
        logStream<<__func__<<" "<<finalProfile.name<<endl;
    }

    void inputPassword(profile &userProfile)
    {
        int globalTry=0;
        string temp;
        do
        {
            //getline(cin, userProfile.password);
            deleteUnwanted(globalTry,3) ;
            userProfile.password= hiddenPasswordInput();
            int triedYet=0;
            while (!isPasswordCorrect(userProfile.password))
            {
                deleteUnwanted(!triedYet,1);
                deleteUnwanted(triedYet,5);
                cout<<fgred;
                cout<<endl;
                cout<<printtabs(8);
                cout << "Your password does not satisfy our conditions"
                     << endl;
                cout<<printtabs(8);
                cout << "Your password should consist of at least one small letter, one capital letter, one number and one special character"
                     << endl;
                cout<<printtabs(8);
                cout << "Try again"
                     <<endl;
                userProfile.password=hiddenPasswordInput();
                delayBy(0.5);
                triedYet=1;
            }
            // cout<<cursorUp;
            // deleteUnwanted(triedYet,3);
            // cout<<cursorDown;
            printOption(8,4,"Confirm your password ");
            cout<<endl;
            temp=hiddenPasswordInput();
            //PRINTBLUE;
            //getline(cin, temp);
            //cin>>temp;
            if (temp != userProfile.password)
            {
                cout<<fgred;
                cout << printtabs(8)<<"Both passwords do not match each other"
                     << endl;
                cout << printtabs(8)<<"Try again"
                     << endl;
                delayBy(2);
                deleteUnwanted(1,2);
            }
            globalTry=1;
            delayBy(1.5);
        } while (temp != userProfile.password);
        cout<<endl;
    }

    profile login()
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
        logging.flush();
        cout << endl;
        password = sha256(password);
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
                userProfile= login();
            }
        }
        assignUserProfile(userProfile);
        return userProfile;
    }

    void sendOTP(string mailID){
        string OTP = "";
        srand(time(0));
        int len = 6;
        for(int i=0;i<len;++i)OTP.push_back((char)(rand()%10 + '0'));
        sendPasswordToEmail(mailID, OTP, "1");
        string tempOTP;
        int tried=0;
        do{
        printOption(8,3,"Please verify your email:: Enter your OTP ");
        cout<<endl;
        printInputField();
        cin>>tempOTP;
        deleteUnwanted(tried,2);
        tried=1;
        }while(tempOTP!=OTP);
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
        }
        int triedYet=0;
        do
        {
            printOption(9, 2, "Contact Number ", 0);
            cout << fgblue << ">>";
            cin >> userProfile.contact;
            delayBy(0.4);

        } while (!isContactCorrect(userProfile.contact,&triedYet));

        cout << endl;
        triedYet=0;
        do
        {
            printOption(9, 2, "e-MAIL ID ", 0);
            cout << fgblue << ">>";
            cin >> userProfile.email;
            delayBy(0.4);

        } while (!isEmailCorrect(userProfile.email,&triedYet));

        cout<<printtabs(8);
        cout << fgred<<"Your username should consist of nothing other than small letters \n"<<
        printtabs(8)<<" and capital letters and numbers \n"
        <<printtabs(8)<<" and underscores"
             << endl;

        printOption(9,0,"Username");
        cout<<fgblue<<">>";
        cin>>userProfile.username;
        triedYet=0;
        while (!isUsernameCorrect(userProfile.username) || systemAdmin.isUsernameTaken(userProfile.username))
        {
            if (!isUsernameCorrect(userProfile.username))
            {
                deleteUnwanted(triedYet,3);
                cout<<printtabs(8);
                cout << fgred<<"Your username does not satisfy our conditions ! ! !"
                     << endl;
            }
            else
            {
                deleteUnwanted(triedYet,3);
                printtabs(8);
                cout<<fgred;
                cout << "This username is taken !!!"
                     << endl;
            }
            cout<<fgred;
            printtabs(8);
            cout << "Try again!!!"
                 << endl;
            printOption(9,0,"Username");
            cout<<fgblue<<">>";
            cin>>userProfile.username;
            delayBy(0.4);
            triedYet=1;
        }
        cout<<endl;
        cout<<fgblue<<printtabs(8);
        cout<<fgred;
        cout << "Your password should consist of at least one small letter\n"+printtabs(8)+", one capital letter, one number and one special character"
             << endl;
        getline(cin,password);
        inputPassword(userProfile);
        printOption(9,0,"Adress ");
        PRINTBLUE;
        cout<<" ";
        getline(cin, userProfile.address);
        sendOTP(userProfile.email);
        userProfile.id =systemAdmin.signUp(userProfile);
        assignUserProfile(userProfile);
    }

    void updateProfile()
    {
        profile changedProfile=systemAdmin.editProfile(userID,finalProfile);
        assignUserProfile(changedProfile);
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
        else{
            systemAdmin.forgotPassword(username);
            cout << printtabs(8) << "New Password has benn sent to your registered email."
                 << "\n";
        }
        delayBy(2.1);
    }

};
