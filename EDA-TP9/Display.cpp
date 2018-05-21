#include "Display.h"



void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	byte rs = (rs_) ? 0x02 : 0x00;
	byte temp = data & 0xf0;
	temp |= rs;				// or igual 
	lcdWriteNyble(handle, temp);
	temp = (data & 0x0F) << 4;
	temp |= rs;
	lcdWriteNyble(handle, temp);
}


bool initDisplay(const char * displayName, FT_HANDLE& display)
{
	
	bool init = false;
	if (FT_OK == FT_OpenEx((PVOID)displayName, FT_OPEN_BY_DESCRIPTION, &display)) 
		if (FT_OK == FT_SetBitMode(display, 0xff, 1)){

			init = true;

			byte bitMode8 = lcdInstructions::funcionSet | lcdInstructions::funcionChs::dataLenght;
			lcd_SendData(bitMode8, true, display);
			wait(4);
			lcd_SendData(bitMode8, true, display);
			wait(1);
			lcd_SendData(bitMode8, true, display);

			byte bitMode4 = lcdInstructions::funcionSet;
			lcd_SendData(bitMode4, true, display);

			// FALTA PASO 7
			byte step7 = lcdInstructions::funcionSet | lcdInstructions::funcionChs::displayLines | lcdInstructions::funcionChs::font;
			lcd_SendData(step7, true, display);

			lcd_SendData(lcdInstructions::displayOnOffControl, true, display);

			lcd_SendData(lcdInstructions::clearScreen, true, display);	

			lcd_SendData(lcdInstructions::entryModeSet, true, display);
		}
	return init;

}

void lcdWriteNyble(FT_HANDLE& h, byte d)
{
	DWORD BytesSent = 0;
	byte temp = 0x00;
	//Bajar enable 
	temp = d & (~ENABLE);
	FT_Write(h,(LPVOID) temp, sizeof(temp), &BytesSent);	// D7 D6 D5 D4 XX RS E
															//	  |_____d_____|			
	wait(0.5);
	//Subir enable
	temp = d | ENABLE;
	FT_Write(h, (LPVOID)temp, sizeof(temp), &BytesSent);
	wait(3);
	//Bajar enable
	temp = d & ~ENABLE;
	FT_Write(h, (LPVOID)temp, sizeof(temp), &BytesSent);
	return;
}

void wait(float ms)
{
	Timer time;

	do {
		time.stop();
	} while (time.getTime() <= ms);
}
