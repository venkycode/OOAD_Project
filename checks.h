#include <bits/stdc++.h>
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