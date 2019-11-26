#include <bits/stdc++.h>
#include <ostream>

namespace Color
{
enum Code
{
    FG_RED = 31,
    FG_GREEN = 32,
    FG_BLUE = 36,
    FG_DEFAULT = 39,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};
class Modifier
{
    Code code;

public:
    Modifier(Code pCode) : code(pCode) {}
    friend std::ostream &
    operator<<(std::ostream &os, const Modifier &mod)
    {
        return os << "\033[" << mod.code << "m";
    }
};
}; // namespace Color
using namespace std;
const string clearscreen = "\033[2J";
const string cursorAdjust = "\033[1;1H";
const string deleteLine="\033[2K";
const string cursorUp="\033[1A";
const string cursorDown="\033[1B";
Color::Modifier bgred(Color::BG_RED);
Color::Modifier fgred(Color::FG_RED);
Color::Modifier fgblue(Color::FG_BLUE);
Color::Modifier fggreen(Color::FG_GREEN);
Color::Modifier bgblue(Color::BG_BLUE);
Color::Modifier bgdef(Color::BG_DEFAULT);

#define PRINTBLUE cout<<fgblue<<">> "

void delayBy(double sec)
{
    double factor = 100000000.0;
    long int timer = 0;
    while (timer < sec * factor)
    {
        int x = sqrt(timer);
        timer++;
    }
}

void printHeader()
{
    cout << clearscreen;
    cout << cursorAdjust;
    cout << "\t\t\t\t\t\t\t\t\t" << bgblue << fgred << "ONLINE DELIVERY SYSTEM " << bgdef << endl;
    cout << endl;
}
void printInputField()
{
    cout << "\t\t\t\t\t\t\t\t\t     " << fggreen << ">>   " << fgblue;
}
string convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

string printtabs(int num)
{
    string s = "";
    for (int i = 1; i <= num; i++)
    {
        s = s + "\t";
    }
    return s;
}

void printOption(int numTabs, int numSpace=0, string option="", int optionNumber=0)
{
    cout << printtabs(numTabs);
    for (int i = 0; i < numSpace; i++)
        cout << " ";
    cout << fggreen;
    cout << option;
    if (optionNumber)
    {
        cout << "[";
        cout << fgred;
        cout << optionNumber;
        cout << fggreen;
        cout << "]";
        cout << endl;
        cout << endl;
    }
    
}
void deleteUnwanted(int flag,int numberOfLines=1)
{
    if (flag==1)
    {
        for(int i=0;i<numberOfLines;i++)
        {cout << cursorUp;
        cout << deleteLine;
        }

    }
}

string hiddenPasswordInput()
{
    char* tmpPassword;
    printOption(9,0,"Password");
    cout<<fgblue<<">> ";
    tmpPassword=getpass("");
    //logStream<<tmpPassword;
    string returnPass=tmpPassword;
    return returnPass;
}

void printLine(int n)
{
    for(int i=0 ; i<n ;i++)
    {
        cout<<fgred <<"-";
    }
    cout<<endl;
}