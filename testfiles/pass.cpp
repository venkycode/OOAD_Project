#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
char *getpass(const char *prompt);
int main()
{
    char* pass=getpass("ENTER PASS:");
    cout<<"entered pass:"<<pass<<endl;
    return 0;

}