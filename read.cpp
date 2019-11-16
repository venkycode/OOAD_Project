#include <bits/stdc++.h>
using namespace std;
class testClass
{
public:
    int x;
    char ch;
    char st[2];
    int array[3];
    //string stc;
    map<int, int> mpx;
};

int main()
{
    ifstream new_file;
    new_file.open("newfile", ios::binary);
    testClass txx;
    new_file.read((char*)&txx,sizeof(txx));

    cout<<txx.x<<endl;
    cout<<txx.ch<<endl;
    cout<<txx.st[0]<<" "<<txx.st[1]<<endl;
    cout<<txx.array[0]<<" "<<txx.array[1]<<" "<<txx.array[2]<<endl;
    cout<<txx.stc<<endl;
    new_file.close();   
    return 0;
}