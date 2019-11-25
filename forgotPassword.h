
#include <Python.h>
#include <bits/stdc++.h>
using namespace std;

void sendPasswordToEmail(string email, string new_password, string check = "0")
{
    Py_Initialize();
    char filename[]="temp";
    FILE* pyfile;
    pyfile=fopen(filename,"r");
    string temp = "i=\""+email+"\"";
    char temp1[temp.size()+1];
    for(int i=0;i<temp.size();++i)temp1[i]=temp[i];
    temp1[temp.size()]='\0';
    temp = "j=\""+new_password+"\"";
    char temp2[temp.size()+1];
    for(int i=0;i<temp.size();++i)temp2[i]=temp[i];//cout<<temp<<' '<<temp2<<endl;
    temp2[temp.size()]='\0';
    temp = "k=\""+check+"\"";
    char temp3[temp.size()+1];
    for(int i=0;i<temp.size();++i)temp3[i]=temp[i];//cout<<temp<<' '<<temp2<<endl;
    temp3[temp.size()]='\0';
    PyRun_SimpleString(temp1);
    PyRun_SimpleString(temp2);
    PyRun_SimpleString(temp3);
    PyRun_SimpleFile(pyfile,filename);
    Py_Finalize();
}