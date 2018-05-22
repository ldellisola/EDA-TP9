/*Trabajo prático n9 de EDA
Grupo 2
Integrantes: 
			Del'Isolla Lucas (58.025)
			Lambertucci Guido (58.009)
			Tolaba Francisco (58.424)

Se ha realizado el driver para el manejo del display lcd de la marca Hitachi y adicionalmente se realizo la simulacion del 
hardware por medio de la libreria grafica de allegro.
Consideraciones para Hitachi lcd: se implementó pd_curses para visualizar un menú a fin de facilitar al usuario las acciones
que puede realizar con este programa.
*/

#include "Display.h"
#include <iostream>
#include "CursesClass.h"
#include "UserHandler.h"
#include "hitachilcd.h"
#include "allegrolcd.h"
using namespace std;

#define TOTAL_CLEAN_KEY 9 	
#define UPCURSOR  KEY_UP
#define DOWNCURSOR KEY_DOWN
#define LEFTCURSOR KEY_LEFT
#define	RIGHTCURSOR KEY_RIGHT
#define CLEAN_KEY 8 //Backspace
#define ESC 27	//Tecla esc
#define STRINGMODE '|'
#define ENTER '\n'

#define TIMEOUT 1500
int main() {

	//hitachilcd  prog( (char *)"EDA LCD 2 B");		//Para simular mediante allegro, comenar esa linea y descomentar la siguiente
	allegrolcd prog(1.0, 2.0);
	if (prog.lcdInitOk())
	{
		prog.lcdClear();
		prog << "Hello Comrade";
		wait(TIMEOUT);
		prog.lcdClear();
		CursesClass curses;
		bool leave = false;
		basicLCD * lcd = &prog;
		printInstructions(curses);
		int ch;
		do {
			ch = getch();
			switch (ch) {
			case ESC:
				leave = true;
				break; // Es escape. Cierra el programa
			case ERR:
				break;			// No pasa nada
			case UPCURSOR:
				if (!lcd->lcdMoveCursorUp())
				{
					error(curses);
					leave = true;
				}
				break;			// Mueve el cursor para arriba
			case DOWNCURSOR:
				if (!lcd->lcdMoveCursorDown()) {
					error(curses);
					leave = true;
				}
				break;		// Mueve el cursor para abajo
			case LEFTCURSOR:
				if (!lcd->lcdMoveCursorLeft()) {
					error(curses);
					leave = true;
				}
				break;		// Mueve el cursor para la izquierda
			case RIGHTCURSOR:
				if (!lcd->lcdMoveCursorRight()) {
					error(curses);
					leave = true;
				}
				break;		// Mueve el cursor a la derecha
			case TOTAL_CLEAN_KEY:
				if (!lcd->lcdClear()) {
					error(curses);
					leave = true;
				}
				break;		// Limpia la pantalla
			case ENTER:
				cursorPosition curr = lcd->lcdGetCursorPosition();
				if ((curr.row != CANT_ROW))
				{
					curr.column = 1;
					curr.row = 2;
					lcd->lcdSetCursorPosition(curr);
				};
				break;
			case STRINGMODE:			// Entra en modo string. Aca el usuario puede escribir un string y se imprime en el lcd
				lcd->lcdClear();
				stringMode(curses, *lcd);
				noecho();
				clear();
				printInstructions(curses);
				break;
			case CLEAN_KEY:
				if (!lcd->lcdMoveCursorLeft()) {
					error(curses);
					leave = true;
				}
				else {
					*lcd << " ";
					lcd->lcdMoveCursorLeft();
				}
				break;	// Borra el ultimo caracter
			default:
				if (isascii(ch)) {		// Lo escribe en pantalla
					cursorPosition curr = lcd->lcdGetCursorPosition();
					if ((curr.column == CANT_COL+1 ) && (curr.row == CANT_ROW))
					{
						lcd->lcdClear();
						*lcd << ch;
					}
					else
						*lcd << ch;
				}
			}
		} while (!leave);

		lcd->lcdClear();
		string t = "c++ string";
		*lcd << t;
		wait(TIMEOUT);
		lcd->lcdClear();
		const char * tt = "c_string";
		*lcd << tt;
		wait(TIMEOUT);
		lcd->lcdClear();
		char a = 'c';
		*lcd << a;
		wait(TIMEOUT);
		lcd->lcdClear();
		prog << "Good bye friend";
		wait(TIMEOUT);
		lcd->lcdClear();
	}
	else {
		cout << "Couldnt initiliaze hardware, please check if is plugged in correctly or if the device is supported by our program." << endl;
		cout << "Enter a key to leave" << endl;
		getchar();
	}
	return 0;
}