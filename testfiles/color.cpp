#include "colormod.h" // namespace Color
#include <iostream>
using namespace std;
int main() {
    Color::Modifier red(Color::BG_RED);
    Color::Modifier def(Color::BG_DEFAULT);
    cout << "This ->" << red << "word" << def << "<- is red." << endl;
}