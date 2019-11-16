#include <bits/stdc++.h>
using namespace std;

enum typeOfUser
{
    Customer,
    deliveryPerson,
    ShopKeeper
};

enum mode
{
    cashOnDelivery,
    onlineBanking,
    Paytm,
    GooglePay
};

typedef struct timex
{
    int days, hours, minutes;
} timex;

typedef struct product
{

} product;

typedef struct profile{
    string name,surname,email;
    string address;
    string username,password;
}profile;

typedef struct order
{
    enum mode paymentMode;
    int customerID;
    int orderID;
    bool isPlaced;
} order;

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