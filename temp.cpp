
#include<bits/stdc++.h>
#include <Python.h>
// #include "header.h"
// #include "sha256.h"
// #include "User.h"



int main()
{
    Py_Initialize();
    char filename[]="temp";
    FILE* pyfile;
    pyfile=fopen(filename,"r");
    PyRun_SimpleString("i=\"pandit.1@iitj.ac.in\"\n");
    PyRun_SimpleFile(pyfile,filename);
    //PyRun_SimpleString("print(i)\n");
    Py_Finalize();
    return 0;
}