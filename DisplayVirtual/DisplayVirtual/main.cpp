#include <time.h>
#include <iostream>
#include "interface.h"
#include "DisplayFran.h"
#include "mzahnd/src/DisplayMartin.hpp"

void delay(float number_of_seconds);

int main() {
	basicLCD* pDisplay;

    //Fran
	displayFran dispF;

    // Martin
    DisplayMartin dispM;


    pDisplay = &dispM;

    /*
    pDisplay = &dispF;
    std::cout << "Todo ok? \t" << pDisplay->lcdInitOk() << std::endl;
    delay(2);
    (*pDisplay) << "Testeando" << " " << "ando??";
    dispM.updateGUI();
    delay(2);
    (*pDisplay) << 'a' << 'b' << ' ' << 'c';
    dispM.updateGUI();
    delay(2);
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    pDisplay->lcdMoveCursorLeft();
    dispM.updateGUI();
    delay(2);
    pDisplay->lcdClearToEOL();
    dispM.updateGUI();
    delay(2);
    pDisplay->lcdMoveCursorDown();
    dispM.updateGUI();
    delay(1);
    pDisplay->lcdMoveCursorRight();
    dispM.updateGUI();
    delay(1);
    (*pDisplay) << "Hola!**";
    pDisplay->lcdMoveCursorUp();
    dispM.updateGUI();
    delay(1);
    if (pDisplay->lcdMoveCursorUp() == false) //Sólo este UP deberia generar un error
    {
        std::cout << "Name: " << (pDisplay->lcdGetError()).getErrorName() << std::endl;
        std::cout << "Descript: " << (pDisplay->lcdGetError()).getErrorDescription() << std::endl;
        std::cout << "Code: " << (pDisplay->lcdGetError()).getErrorCode() << std::endl;
    }

    delay(1);
    pDisplay->lcdMoveCursorLeft();
    delay(1);
    (*pDisplay) << "curry desde" << "otra dimension";
    delay(2);
    pDisplay->lcdClear();
    delay(2);
 */

    return dispM.gui();
}

void delay(float number_of_seconds)
{
    // Convertimos a milis 
    float milli_seconds = 1000 * number_of_seconds;

    // Guardamos el tiempo 
    clock_t start_time = clock();

    // Congelamos el codigo hasta que se cumpla el tiempo 
    while (clock() < start_time + milli_seconds);
}