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

bool queryUser(std::string msg)
{
    std::string ans;
    std::cout << msg;
    std::cin >> ans;
    if (ans == "y" || ans == "Y") {
        return true;
    }

    return false;
}

int main() {
    //Fran
	displayFran dispF;

    // Martin
    DisplayMartin dispM;

    // Trini
    displayTrini dispT;

    basicLCD* pDisplay[DISPLAYS_TO_TEST] = {&dispF, &dispT, &dispM};

    if (queryUser("Run tests? [Y/N] ")) {
        // Tests :)
        tests(pDisplay, DISPLAYS_TO_TEST);
    }

    if (queryUser("All test have finished.\nWould you like to see an easter egg? :D [Y/N] "))
    {
        const cursorPosition easterEgg = { 0xEA, 0xE6 };
        pDisplay[DISPLAY_MARTIN]->lcdSetCursorPosition(easterEgg);
    }
    return 0;
}
