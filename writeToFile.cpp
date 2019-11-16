#include <bits/stdc++.h>
using namespace std;
class testClass
{
public:
    int x;
    char ch;
    char st[2];
    int array[3];
    string stc;
    map<int, int> mpx;
    testClass()
    {
        stc.resize(10);
    }
};

int main()
{
    fstream new_file;
    new_file.open("newfile", ios::out|ios::binary);
    testClass tmp;
    tmp.x = 10;
    tmp.ch = 'a';
    tmp.st[0]  = 'v';
    tmp.st[1]='e';
    tmp.array[0]=1;
    tmp.array[1]=2;
    tmp.array[2]=3;
    tmp.stc = "Venkatesh";
    for(int i=1;i<4; i++ )
    {
        tmp.mpx.insert(make_pair(i,i*i));
    }

    new_file.write((char*)&tmp,sizeof(tmp));
    new_file.close();

    return 0;
}