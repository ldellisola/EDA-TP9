#include "UserHandler.h"

void stringMode(CursesClass & curses, basicLCD& display)
{
	clear();
	mvprintw(0, 0, "Type any string and watch it appear in the frikkin' lcd");
	string a = curses.getString(2, 0, 17 * 2);

	display << a;
}

void error(CursesClass & curses)
{
	clear();
	mvprintw(0, 0, "There has been an error and we are shutting down. Press any key to continue");
	curses.getSingleLoweredCharInRange(0, 255 , 2, 0, "Vos sos tonto");
}

void printInstructions(CursesClass & curses)
{
	move(0, 0);
	printw("Hello and welcome to EDA-TP9. Do as I say and nothing will ever happen to your family, do otherwise and you'll see...\n");
	printw("\n");
	printw("Use the 'W', 'A', 'S' or 'D' (case sensitive!) to navigate around the display\n");
	printw("Press '|' to clear the screen");
	printw("Press any key to write");
	printw("Press 'esc' to leave the program\n");
}
