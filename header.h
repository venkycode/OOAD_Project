#include <bits/stdc++.h>
using namespace std;

int getFileSize(const std::string &fileName)
{
    ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

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
    int product_id;
    int product_type;
    char product_name[10];
    int deliveryCharge;
    int rating=0;                   //rating of the product
    char shopkeeper_id[10];

} product;

typedef struct profile{
    string name,surname,email;
    string address;
    string username,password;
    string contact;
    string id;
    enum typeOfUser type;
    bool isBlackListed;
}profile;

typedef struct order
{
    enum mode paymentMode;
    int customerID;
    int orderID;
    bool isPlaced;
} order;



