#include"frontend.h" // contains all the headers required to run the program

int main()
{
    logStream << "\n\n>>> !!! START OF LOG !!! <<<<<\n";
    cout << clearscreen;
    cout << cursorAdjust; 
    mainPage(); // starts with main page
    logStream << ">>> !!! END OF LOG !!! <<<<<\n";
    logging.close();
}
