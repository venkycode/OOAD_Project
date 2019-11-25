#include "Customer.h"
using namespace std;

User tmpUser;


int main()
{
    tmpUser.emailID="ssss@iitj.ac.in";
    tmpUser.isLoggedIn=0;
    customer* cust=dynamic_cast<customer*>(&tmpUser);
    cout<<cust.emailID;
    tmpUser->updateProfile();
    return 0;
}