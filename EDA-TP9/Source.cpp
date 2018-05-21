#include "Display.h"
#include <iostream>
#include "CursesClass.h"
#include "UserHandler.h"
#include "hitachilcd.h"
#include "allegrolcd.h"
using namespace std;


int main() {

	//hitachilcd  prog( (char *)"EDA LCD 2 B");
	allegrolcd prog(1.0, 2.0);

	CursesClass curses;
	bool leave = false;
	basicLCD * lcd = &prog;
	printInstructions(curses);
	int ch;
	do {
		ch = getch();
		switch (ch) {
		case 27: leave = true; break; // Es escape. Cierra el programa
		case ERR: break;			// No pasa nada
		case KEY_UP:
			if (!lcd->lcdMoveCursorUp()) {
				error(curses);
				leave = true;
			}
			break;			// Mueve el cursor para arriba
		case KEY_DOWN:
			if (!lcd->lcdMoveCursorDown()) {
				error(curses);
				leave = true;
			}
			break;		// Mueve el cursor para abajo
		case KEY_LEFT:
			if (!lcd->lcdMoveCursorLeft()) {
				error(curses);
				leave = true;
			}
			break;		// Mueve el cursor para la izquierda
		case KEY_RIGHT:
			if (!lcd->lcdMoveCursorRight()) {
				error(curses);
				leave = true;
			}
			break;		// Mueve el cursor a la derecha
		case KEY_CATAB:

			if (!lcd->lcdClear()) {
				error(curses);
				leave = true;
			}

			break;		// Limpia la pantalla
		case KEY_SHIFT_L:			// Entra en modo string. Aca el usuario puede escribir un string y se imprime en el lcd
		case KEY_SHIFT_R:
			stringMode(curses, *lcd);
			clear();
			printInstructions(curses);
			break;
		case KEY_BACKSPACE:
			if (!lcd->lcdMoveCursorLeft()) {
				error(curses);
				leave = true;
			}
			else {
				*lcd << " ";
			}

			break;	// Borra el ultimo caracter
		default:
			if (isalnum(ch)) {		// Lo escribe en pantalla
				*lcd << ch;
			}

		}


	} while (!leave);


	return 1;
}