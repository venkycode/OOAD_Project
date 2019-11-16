#include<bits/stdc++.h>
#include "header.h"

using namespace std;

int main()
{
    ifstream filex;
    filex.open("newfile.txt", ios::in);
    admin testAdmin;
    filex.read((char*)&testAdmin,sizeof(testAdmin));
    cout<<testAdmin.emailID<<endl;
    for(int i=0;i<10;i++)  cout<<testAdmin.array[i];
    return  0;
}