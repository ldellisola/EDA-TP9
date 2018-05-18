#include "Display.h"



int main() {

	FT_HANDLE display = initDisplay("EDA LCD 2 B");
	lcdWriteNyble(display, 0x30);

	return 1;
}