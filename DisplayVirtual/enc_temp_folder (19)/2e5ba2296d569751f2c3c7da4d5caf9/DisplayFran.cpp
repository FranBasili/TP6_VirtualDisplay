#include <iostream>
#include "DisplayFran.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#define ROWMAX	1
#define COLMAX	15
#define CHARS	((ROWMAX+1)*(COLMAX+1))
#define POSACTUAL (cursor.column + cursor.row * COLMAX)


#define DISPLAYWIDTH	330
#define DISPLAYHEIGHT	147
#define BLACK		al_map_rgb(0, 0 ,0)
#define XOFFSET		40
#define YOFFSET		55
#define CHARDISTX	16
#define CHARDISTY	25
#define POSX(col)	((col)*CHARDISTX + XOFFSET)
#define POSY(row)	((row)*CHARDISTY + YOFFSET)
#define RECT_HEIGH	20
#define RECT_WIDTH	5

using namespace std;

static ALLEGRO_DISPLAY* display;
static ALLEGRO_FONT* font;
static ALLEGRO_BITMAP* bitmapBackground;

bool initAllegro(lcdError& error);
bool destroyAllegro();

displayFran:: displayFran(){
		
	initOk = true;

	//Limpiamos el display
	initOk &= clearDisplay({ 0,0 }, {ROWMAX,COLMAX});

	initOk &= initAllegro(error);

	if (initOk == false) {
		destroyAllegro();
	}
	cursor.column = 0;
	cursor.row = 0;

	this->updateDisplay();
}

displayFran:: ~displayFran(){
	clearDisplay({0,0}, {ROWMAX,COLMAX});
	destroyAllegro();
}

bool displayFran :: lcdInitOk() {
	return	initOk;
}

lcdError& displayFran::lcdGetError() {
	return this->error;
}

bool displayFran::lcdClear() {
	if (!clearDisplay({0,0}, {ROWMAX,COLMAX})) {
		error.setError("Cleaning error.", "The display can't be cleaned", FAIL_CLEAR);
		return false;
	}
		
	updateDisplay();
	return true;
}

bool displayFran::lcdClearToEOL() {
	if (!clearDisplay(cursor, {cursor.row, COLMAX})) {
		error.setError("Cleaning error.", "The display can't be cleaned to EOL", FAIL_CLEAR);
		return false;
	}
		
	updateDisplay();
	return true;
}

basicLCD& displayFran :: operator<< (const char c) {
	text[POSACTUAL] = c;
		
	if (cursor.column == COLMAX && cursor.row < ROWMAX) {
		cursor.row++;
		cursor.column = 0;
	}
	else if (cursor.column < COLMAX) {
		cursor.column++;
	}
	updateDisplay();
	return *this;
}

basicLCD& displayFran:: operator<<(const char* c) {
	string temp((const char*)c);
	int tempSize = (int) temp.size();
	
	if ((CHARS - POSACTUAL) > (int)temp.size()){
		// Si el largo del arreglo de chars es menor a la cantidad de caracteres libres, 
		//cargo el arreglo de chars completo. 
		text.replace(text.begin() + POSACTUAL, text.begin() + POSACTUAL + tempSize, temp.begin(), temp.end());
			
		if ((cursor.column += tempSize) > COLMAX) {
			if(cursor.row < ROWMAX) 
				cursor.row++;
			cursor.column = cursor.column % ROWMAX;
		}

	}
	else {
		// Si el largo del arreglo de chars es mayor a la cantidad de caracteres libres, 
		//cargo los chars que entren de atras para adelante.
		text.replace(text.begin() + POSACTUAL, text.end(), temp.end()- (CHARS - POSACTUAL), temp.end());

		cursor.row = ROWMAX;
		cursor.column = COLMAX;
	}
	updateDisplay();
	return *this;
}

bool displayFran::lcdMoveCursorUp()
{
	if (cursor.row > 0)
	{
		cursor.row-=1;
		updateDisplay();
		return true;
	}
	else
	{

		error.setError("Up Boundry error.", "The cursor is already in the high boundary", UP_BOUNDARY);
		return false;
	}
	updateDisplay();
}

bool displayFran::lcdMoveCursorDown()
{
	if (cursor.row < ROWMAX)
	{
		cursor.row+=1;
		updateDisplay();
		return true;
	}
	else
	{
		error.setError("Down Boundry error.", "The cursor is already in the low boundary", DOWN_BOUNDARY);
		return false;
	}
}

bool displayFran::lcdMoveCursorRight() {
	if (cursor.column < COLMAX)
	{
		cursor.column++;
		updateDisplay();
		return true;
	}
	else
	{
		if (cursor.row == COLMAX)
		{

			error.setError("Right Boundry error.", "The cursor is already in the right boundary", RIGHT_BOUNDARY);
			return false;
		}
		else
		{
			cursor.column = 0;
			cursor.row++;
			updateDisplay();
			return true;
		}
	}
	updateDisplay();
}

bool displayFran::lcdMoveCursorLeft() {
	
	if (cursor.column >= 1)
	{
		cursor.column--;
		updateDisplay();
		return true;
	}
	else
	{
		if (cursor.row <= 0)
		{
			error.setError("Left Boundry error.", "The cursor is already in the left boundary", LEFT_BOUNDARY);

			return false;
		}
		else
		{
			cursor.column = COLMAX;
			cursor.row--;
			updateDisplay();
			return true;
		}
	}
	updateDisplay();
}

bool displayFran::lcdSetCursorPosition(const cursorPosition pos) {
	if (pos.row <= COLMAX && pos.row >= 0 && pos.column >= 0 && pos.column <= ROWMAX)
	{
		cursor.row = pos.row;
		cursor.column = pos.column;
		return true;
	}
	else 
	{
		error.setError("Cursor Out of bounds", "The cursor position is bigger than the display.", OUT_OF_BOUNDS);
		return false;
	}
}

cursorPosition displayFran::lcdGetCursorPosition(){
	return cursor;
}

bool displayFran::updateDisplay() {
	
	al_draw_bitmap(bitmapBackground, 0.0, 0.0, 0);

	for (int row = 0; row <= ROWMAX; row++) {
		for (int col = 0; col <= COLMAX; col++) {
			char c = text[row * COLMAX + col];
			al_draw_text(font, BLACK, POSX(col), POSY(row), ALLEGRO_ALIGN_LEFT, &c);
		}
	}

	al_draw_filled_rectangle(POSX(cursor.column), POSY(cursor.column)-6, POSX(cursor.column) + RECT_WIDTH, POSY(cursor.column)+RECT_HEIGH+2-5, BLACK);
	al_flip_display();

	return	true;
}

bool displayFran::clearDisplay(cursorPosition cursor, cursorPosition cursorf)
{
	try {
		int posi = cursor.column + cursor.row * COLMAX;
		int posf = cursorf.row * COLMAX + cursorf.column;
		text = text.replace(posi, 1, posf - posi, ' ');
	}
	catch (const std::out_of_range& oor)
	{
		cout << oor.what() << endl;
		return false;
	}

	catch (const std::length_error& l_)
	{
		cout << l_.what() << endl;
		return false;
	}

	catch (const std::bad_alloc& ba)
	{
		cout << ba.what() << endl;
		return false;
	}

	return true;
}

bool initAllegro(lcdError& error) {
	if (!al_init()){
		error.setError("Initializing allegro error", "An error ocurred while al_init()", ALINIT);
		return false;
	}

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	display = al_create_display(DISPLAYWIDTH, DISPLAYHEIGHT);
	bitmapBackground = al_load_bitmap("displayFran.png");
	font = al_load_ttf_font("FontFran.ttf", 16, 0);

	if (display == NULL){
		error.setError("Display Error", "Error creating display", DISPLAY);
		return false;
	}
	else if (bitmapBackground == NULL) {
		error.setError("Background error.", "Error loading the background", BACKGROUND);
		cout << "Pincho bitmap" << endl;
			return false;

	} else if (font == NULL) {
		error.setError("Font error", "Error loading the font", FONT);
		cout << "Pincho font" << endl;
			return false;
	}

	return true;
}

bool destroyAllegro() {
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_bitmap(bitmapBackground);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();

	return true;
}