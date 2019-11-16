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
    bool isBlackListed;
}profile;

typedef struct order
{
    enum mode paymentMode;
    int customerID;
    int orderID;
    bool isPlaced;
} order;

bool isContactCorrect(string contact){
    return contact.size()==10;
}

bool isEmailCorrect(string email){
    int n = email.size();
    int pos=-1;
    string collegeID = "iitj.ac.in";
    for(int i=0;i<n;++i){
        if(email[i]=='@'){pos=i+1;break;}
    }
    if(pos==-1 || n-pos!=collegeID.size())return 0;
    bool check=1;
    for(int i=pos;i<n;++i){
        if(email[i]!=collegeID[i-pos]){
            check=0;break;
        }
    }
    return check;
}