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
 
typedef struct timeStamp
{
    int days, hours, minutes;
} timeStamp;
 
typedef struct product
{
    int product_id;
    int product_type;
    char product_name[10];
    int deliveryCharge;
    int rating=0;                   //rating of the product
    char shopkeeper_id[10];
    int count,price;
} product;
 
typedef struct profile{
    string name,surname,email;
    string address;
    string username,password;
    string contact;
    string id;
    enum typeOfUser type;
}profile;
 
typedef struct order
{
    product Product;
    int orderID;
    timeStamp remainingTime;
} order;
 
 
 