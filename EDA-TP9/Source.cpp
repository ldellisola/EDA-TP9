#include "Display.h"
#include <iostream>

using namespace std;


int main() {

	FT_HANDLE display;
	if (initDisplay("EDA LCD 2 B", display)) {
		cout << "init yes display" << endl;
		lcd_SendData( 0x30, false,display);
	}
	else
		cout << "init not display" << endl;

	cin.get();

	return 1;
}