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

#define TOTAL_CLEAN_KEY '|'	
#define UPCURSOR 'W'
#define DOWNCURSOR 'S'
#define LEFTCURSOR 'A'
#define	RIGHTCURSOR 'D'
#define CLEAN_KEY ' '
#define ESC 27	//Tecla esc

int main() {

	hitachilcd  prog( (char *)"EDA LCD 2 B");		//Para simular mediante allegro, comenar esa linea y descomentar la siguiente
	//allegrolcd prog(1.0, 2.0);
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
			{		error(curses);
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
		case KEY_SHIFT_L:			// Entra en modo string. Aca el usuario puede escribir un string y se imprime en el lcd
		case KEY_SHIFT_R:
			stringMode(curses, *lcd);
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
			if (isalnum(ch)) {		// Lo escribe en pantalla
				*lcd << ch;
			}
		}
	} while (!leave);
	
	lcd->lcdClear();
	prog << "Good bye friend";
	wait(3000);
	lcd->lcdClear();

	return 0;
}