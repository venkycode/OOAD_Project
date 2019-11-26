#include <bits/stdc++.h>
using namespace std;

static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{
    return alphanum[rand() % stringLength];
}

string PasswordGenerator()
{
    srand(time(0));
    string password = "";
    int len = rand() % 3 + 8;
    bool countUpperCase = 0, countLowerCase = 0, countNumber = 0, countSpecial = 0;
    for (int i = 0; i < len; i++)
    {
        password += genRandom();
        if (password[i] >= 'a' && password[i] <= 'z')
            countLowerCase = 1;
        else if (password[i] >= 'A' && password[i] <= 'Z')
            countUpperCase = 1;
        else if (password[i] >= '0' && password[i] <= 9)
            countNumber = 1;
        else
            countSpecial = 1;
    }
    if (!countLowerCase)
    {
        password.push_back((char)(rand() % 26 + 'a'));
    }
    if (!countUpperCase)
    {
        password.push_back((char)(rand() % 26 + 'A'));
    }
    if (!countNumber)
    {
        password.push_back((char)(rand() % 10 + '0'));
    }
    if (!countSpecial)
    {
        string temp = "!@#$%^&*";
        password.push_back(temp[rand() % temp.size()]);
    }
    return password;
}
