#include "Display.h"



int main() {

	FT_HANDLE display;
	if (initDisplay("EDA LCD 2 B", display))
		lcdWriteNyble(display, 0x30, false);

	return 1;
}