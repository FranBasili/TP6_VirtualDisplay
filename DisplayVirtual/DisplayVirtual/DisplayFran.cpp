#include "interface.h"
#define ROWMAX	1
#define COLMAX	19

class displayFran : basicLCD
{
public:
	displayFran(): basicLCD(){
	}

	~displayFran(){
	}

	virtual bool lcdInitOk() {}

	virtual FT_STATUS lcdGetError() {}

	virtual bool lcdClear() {};

	virtual bool lcdClearToEOL() {}

	virtual basicLCD& operator<< (const unsigned char c) {}

	virtual bool lcdMoveCursorUp() {}

	virtual bool lcdMoveCursorDown(){}

	virtual bool lcdMoveCursorRight() {
		if (cursor.column < COLMAX)
		{
			cursor.column++;
			return true;
		}
		else
		{
			if (cursor.row == COLMAX)
			{
				return false;
			}
			else
			{
				cursor.column = 0;
				cursor.row++;
				return true;
			}
		}
	}

	virtual bool lcdMoveCursorLeft() {
	
		if (cursor.column >= 1)
		{
			cursor.column--;
			return true;
		}
		else
		{
			if (cursor.row <= 0)
			{
				return false;
			}
			else
			{
				cursor.column = COLMAX;
				cursor.row--;
				return true;
			}
		}
	}

	virtual bool lcdSetCursorPosition(const cursorPosition pos) {
		if (pos.row <= COLMAX && pos.row >= 0 && pos.column >= 0 && pos.column <= ROWMAX)
		{
			cursor.row = pos.row;
			cursor.column = pos.column;
			return true;
		}
		else 
		{
			return false;
		}
	}

	virtual cursorPosition lcdGetCursorPosition(){
		return cursor;
	}

private:
	bool updateDisplay() {}
	cursorPosition cursor;
	lcdError error;

};