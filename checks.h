#include "header.h"
using namespace std;

bool isUsernameCorrect(string username)
{
    for (auto y : username)
    {
        if ((y >= 'a' && y <= 'z') || (y >= '0' && y <= '9') || (y >= 'A' && y <= 'Z') || y == '_')
            ;
        else
            return 0;
    }
    return 1;
}

bool isPasswordCorrect(string password)
{
    if (password.size() < 8)
        return 0;
    bool isSmallLetter = 0, isCapitalLetter = 0, isNumber = 0, isSpecialCharacter = 0;
    for (auto y : password)
    {
        if (y >= 'a' && y <= 'z')
            isSmallLetter = 1;
        else if (y >= 'A' && y <= 'Z')
            isCapitalLetter = 1;
        else if (y >= '0' && y <= '9')
            isNumber = 1;
        else
            isSpecialCharacter = 1;
    }
    return (isSpecialCharacter & isNumber) & (isSmallLetter & isCapitalLetter);
}

bool isContactCorrect(string contact, int *tried = NULL)
{
    int dummyVar = 0;
    if (tried == NULL)
    {
        tried = &dummyVar;
    }
    int len = contact.size();
    if (len != 10)
    {
        cout << cursorUp;
        cout << deleteLine;
        if (*tried == 1)
        {
            cout << cursorUp;
            cout << deleteLine;
        }
        cout << printtabs(9);
        cout << fgred << "Invalid contact number .." << endl;
        *tried = 1;
        return 0;
    }
    for (int i = 0; i < 10; ++i)
    {
        if (contact[i] < '0' || contact[i] > '9')
        {
            cout << cursorUp;
            cout << deleteLine;
            if (*tried == 1)
            {
                cout << cursorUp;
                cout << deleteLine;
            }
            cout << printtabs(8);
            cout << fgred << "Invalid contact number .." << endl;
            //cout<<"here we are"<<endl;
            *tried = 1;
            return 0;
        }
    }
    return 1;
}

bool isEmailCorrect(string email, int *tried = NULL)
{
    int dummyVar = 0;
    if (tried == NULL)
    {
        tried = &dummyVar;
    }
    int n = email.size();
    int pos = -1;
    string collegeID = "iitj.ac.in";
    for (int i = 0; i < n; ++i)
    {
        if (email[i] == '@')
        {
            pos = i + 1;
            break;
        }
    }
    if (pos == -1 || n - pos != collegeID.size())
    {
        cout << cursorUp;
        cout << deleteLine;
        if (*tried == 1)
        {
            cout << cursorUp;
            cout << deleteLine;
        }
        cout << printtabs(9);
        cout << fgred << "Invalid Email Id.. Only use IITJ email id" << endl;
        *tried = 1;

        return 0;
    }
    bool check = 1;
    for (int i = pos; i < n; ++i)
    {
        if (email[i] != collegeID[i - pos])
        {
            cout << cursorUp;
            cout << deleteLine;
            if (*tried == 1)
            {
                cout << cursorUp;
                cout << deleteLine;
            }
            cout << printtabs(9);
            cout << fgred << "Invalid Email Id.. Only use IITJ email id" << endl;
            *tried = 1;

            return 0;
        }
    }
    return check;
}

bool isCorrectCardNumber(string cardNumber)
{
    int len = cardNumber.size();
    if (len != 20)
        return 0;
    int pos = 4;
    bool fl = 1;
    for (int i = 0; i < 19; ++i)
    {
        if (i == pos && cardNumber[pos] != '-')
            fl = 0;
        else if (pos == i)
            pos += 5;
        else if (!(cardNumber[i] >= '0' && cardNumber[i] <= '9'))
            fl = 0;
    }
    return fl;
}

bool isCorrectDate(string date)
{
    int len = date.size();
    if (len != 5 || date[2] != '/' || date[0] < '0' || date[0] > '1' || date[1] < '0' || date[1] > '9' || date[3] != '2' ||
        date[4] < '0' || date[4] > '9')
        return 0;
}

bool isCorrectCvv(string Cvv)
{
    int len = Cvv.size();
    if (len != 3)
        return 0;
    for (int i = 0; i < 3; ++i)
        if (Cvv[i] < '0' || Cvv[i] > '9')
            return 0;
    return 1;
}