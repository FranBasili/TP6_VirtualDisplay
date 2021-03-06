#include <iostream>

#include "DisplayFran.h"
#include "mzahnd/src/DisplayMartin.hpp"

#include "displayTest.h"

enum {
    DISPLAY_FRAN,
    //DISPLAY_TRINI,
    DISPLAY_MARTIN,
    DISPLAYS_TO_TEST
};

int main() {
    //Fran
	displayFran dispF;

    // Martin
    DisplayMartin dispM;

    basicLCD* pDisplay[DISPLAYS_TO_TEST] = { &dispF};
    //basicLCD* pDisplay[DISPLAYS_TO_TEST] = {&dispF, &dispM};

    tests(pDisplay, DISPLAYS_TO_TEST);

    //std::string seeEaster;
    //std::cout << "All test have finished.\n"
    //    << "Would you like to see an easter egg? :D [Y/N] ";
    //std::cin >> seeEaster;
    //if (seeEaster.compare("y") || seeEaster.compare("Y")) {
    //    const cursorPosition easterEgg = { 0xEA, 0xE6 };
    //    pDisplay[DISPLAY_MARTIN]->lcdSetCursorPosition(easterEgg);
    //}
    //
    return 0;
}
