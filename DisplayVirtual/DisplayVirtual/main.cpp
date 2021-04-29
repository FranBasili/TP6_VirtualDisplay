#include <iostream>

#include "DisplayFran.h"
#include "displayTrini.h"
#include "mzahnd/src/DisplayMartin.hpp"

#include "displayTest.h"

enum {
    DISPLAY_FRAN,
    DISPLAY_TRINI,
    DISPLAY_MARTIN,
    DISPLAYS_TO_TEST
};

int main() {
    //Fran
	displayFran dispF;

    // Martin
    DisplayMartin dispM;

    // Trini
    displayTrini dispT;

    basicLCD* pDisplay[DISPLAYS_TO_TEST] = {&dispF, &dispT, &dispM};

    // Tests :)
    tests(pDisplay, DISPLAYS_TO_TEST);

    std::string seeEaster;
    std::cout << "All test have finished.\n"
        << "Would you like to see an easter egg? :D [Y/N] ";
    std::cin >> seeEaster;
    if (seeEaster == "y" || seeEaster == "Y") {
        const cursorPosition easterEgg = { 0xEA, 0xE6 };
        pDisplay[DISPLAY_MARTIN]->lcdSetCursorPosition(easterEgg);
    }
    
    return 0;
}
