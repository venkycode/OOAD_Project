#include"frontend.h"

int main()
{
    logStream << "\n\n>>> !!! START OF LOG !!! <<<<<\n";
    cout << clearscreen;
    cout << cursorAdjust;
    mainPage();
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    logging.close();
}
