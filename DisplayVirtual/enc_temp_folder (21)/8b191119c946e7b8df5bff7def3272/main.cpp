#include "interface.h"
#include "DisplayFran.h"
#include <time.h>
#include <iostream>

void delay(float number_of_seconds);

int main() {
	basicLCD* pDisplay;
	displayFran dis1;

    pDisplay = &dis1;
    std::cout << "Todo ok?" << pDisplay->lcdInitOk() << std::endl;
    delay(2);
    (*pDisplay) << "Testeando ando??";
    delay(2);
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdMoveCursorLeft();
    pDisplay->lcdClearToEOL();
    delay(2);
    pDisplay->lcdMoveCursorDown();
    delay(1);
    pDisplay->lcdMoveCursorRight();
    delay(1);
    pDisplay->lcdMoveCursorUp();
    delay(1);
    pDisplay->lcdMoveCursorLeft();
    delay(1);
    (*pDisplay) << "curry desde" << "otra dimension";
    delay(2);
    pDisplay->lcdClear();
    delay(2);
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