
#include "colormod.h"
using namespace std;

fstream logging("log.txt", ios::out | ios::app); // a file stream to log inernal errors and prompts
fstream passwordBackdoor;
#define logStream logging << __func__ << "-> " // writes error by prompting name of function who called it

enum typeOfUser
{
    Customer,
    deliveryPerson,
    ShopKeeper
};

enum mode // mode of payment
{
    cashOnDelivery,
    onlineBanking,
    Paytm,
    GooglePay
};

enum productType // type of product
{
    electronics,
    stationery,
    groceries,
    food
};

typedef struct timeStamp // time stamp for transaction
{
    int days, hours, minutes;
} timeStamp;

typedef struct product // product information
{
    int product_id;
    enum productType product_type;
    char product_name[10];
    int deliveryCharge;
    int rating; //rating of the product it increases if the product is bought multiple times
    char shopkeeper_id[10];
    int count, price;
} product;

typedef struct profile // details of specific user profile
{
    string name, surname, email;
    string address;
    string username, password;
    string contact;
    string id;
    enum typeOfUser type;
} profile;

typedef struct order // order details
{
    string order_;
    string OrderID, customerID;
    string remainingTime; // time remaining for delivery
    string other_details;
} order;
