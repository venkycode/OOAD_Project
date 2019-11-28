
#include"colormod.h"
using namespace std;

fstream logging("log.txt",ios::out|ios::app);
fstream passwordBackdoor;
#define logStream logging<<__func__<<"-> "

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

enum productType
{
    electronics,
    stationery,
    groceries,
    food
};
 
typedef struct timeStamp
{
    int days, hours, minutes;
} timeStamp;
 
typedef struct product
{
    int product_id;
    enum productType product_type;
    char product_name[10];
    int deliveryCharge;
    int rating;                   //rating of the product
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
    string order_;
    string OrderID ,customerID;
    string remainingTime;
    string other_details;
} order;
 
 
 