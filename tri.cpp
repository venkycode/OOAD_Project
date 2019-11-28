#include "ShopKeeper.h"
using namespace std;

User *tmpUser;


int main()
{

    logStream << ">>> !!! START OF LOG !!! <<<<<\n";
    cout << clearscreen;
    cout << cursorAdjust;
    systemAdmin.deleteID("C2","");
    systemAdmin.deleteID("C4","ganpa");
    systemAdmin.deleteID("C0","qq");
    systemAdmin.deleteID("D0","eee");
    systemAdmin.deleteID("S0","q");
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    logging.close();
}