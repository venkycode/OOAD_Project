#include <Python.h>
#include <bits/stdc++.h>
using namespace std;

void sendPasswordToEmail(string email, string new_password, int check = 0)
{
    Py_Initialize();
    char filename[]="temp";
    FILE* pyfile;
    pyfile=fopen(filename,"r");
    string temp = "i=\""+email+"\"";
    char temp1[temp.size()+1];
    for(int i=0;i<temp.size();++i)temp1[i]=temp[i];
    temp1[temp.size()]='\0';
    if(check){
        new_password = "\nYour OTP is: " + new_password;
    }
    else {
        new_password = "\nYour new password is: " + new_password;
    }
    temp = "j=\""+new_password+"\"";
    char temp2[temp.size()+2];
    for(int i=0;i<temp.size();++i)temp2[i]=temp[i];
    temp2[temp.size()]= check+'0';
    temp2[temp.size()+1]='\0';
    PyRun_SimpleString(temp1);
    PyRun_SimpleString(temp2);
    //PyRun_SimpleFile(pyfile,filename);
    PyRun_SimpleString("print(i)\n");
    Py_Finalize();
}