#include<bits/stdc++.h>
#include <Python.h>
using namespace std;
// #include "header.h"
// #include "sha256.h"
// #include "User.h"

void sendPasswordToEmail(string email, string new_password)
{
    Py_Initialize();
    char filename[]="temp";
    FILE* pyfile;
    pyfile=fopen(filename,"r");
    string temp = "i=\""+email+"\"";
    char temp1[temp.size()];
    for(int i=0;i<temp.size();++i)temp1[i]=temp[i];
    temp = "j=\""+new_password+"\"";
    char temp2[temp.size()+1];
    for(int i=0;i<temp.size();++i)temp2[i]=temp[i];
    temp2[temp.size()]='\0';
    PyRun_SimpleString(temp1);
    PyRun_SimpleString(temp2);
    PyRun_SimpleFile(pyfile,filename);
    PyRun_SimpleString("print(i)\n");
    Py_Finalize();
}
