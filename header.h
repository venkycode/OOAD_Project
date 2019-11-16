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
    int product_id;
    int product_type;
    char product_name[10];
    int deliveryCharge;
    char shopkeeper_id[10];

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
