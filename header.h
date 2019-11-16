#include <bits/stdc++.h>
using namespace std;

template<typename T>
T Min(T v) {
  return v;
}
template<typename T, typename... Args>
T Min(T first, Args... args) {
  return min(first , Min(args...));
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

int editDist(string str1 , string str2 , int m ,int n) 
{ 
	if (m == 0) return n; 
	if (n == 0) return m; 
	if (str1[m-1] == str2[n-1]) 
		return editDist(str1, str2, m-1, n-1); 
	return 1 + Min ( editDist(str1, str2, m, n-1),  
					editDist(str1, str2, m-1, n), 
					editDist(str1, str2, m-1, n-1)  
				); 
} 

bool isMatch(string str1 ,string str2){
    //str1 is the correct name while str2 is not correct
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    string temp="";
    for(int i=0;i<str2.size();++i){
        if(str2[i]>='A'&&str2[i]<='Z')str2[i]-=32;
        if(str2[i]>='a'&&str2[i]<='z')temp+=str2[i];
    }
    str2=temp;
    int dist = editDist(str1, str2, str1.size(), str2.size());
    int countStr1[26];
    memset(countStr1,0,sizeof(countStr1));
    for(int i=0;i<str1.size();++i){
        countStr1[str1[i]-'a']++;
    }
    for(int i=0;i<str2.size();++i){
        countStr1[str2[i]-'a']--;
    }
    int check=0;
    for(int i=0;i<26;++i){
        check+=abs(countStr1[i]);
    }
    long double not_match = dist*check/str1.size()/str2.size();
    return not_match<=0.2?1:0;
}