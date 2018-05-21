#include "Display.h"




void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{

	lcdWriteNyble(handle, data >> 4, rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.

	//byte rs = (rs_) ? 0x02 : 0x00;
	//byte temp = data & 0xf0;
	//temp |= rs;				// or igual 
	//lcdWriteNyble(handle, temp);
	//temp = (data & 0x0F) << 4;
	//temp |= rs;
	//lcdWriteNyble(handle, temp);
}


bool initDisplay(const char * displayName, FT_HANDLE& display)
{
	bool init = false;
	if (FT_OK == FT_OpenEx((PVOID)displayName, FT_OPEN_BY_DESCRIPTION, &display)) {
		byte allPins = 0xff, asyncMode = 1;

		if (FT_OK == FT_SetBitMode(display, allPins, asyncMode)) {

			init = true;
			 // Mando 3 veces el modo de 8 bits
			lcdWriteNyble(display, 0x03, true);
			 wait(4);
			lcdWriteNyble(display, 0x03, true);
			wait(1);
			lcdWriteNyble(display, 0x03, true);
			 // Mando una vez el modo de 4 bits
			lcdWriteNyble(display, 0x02, true);
		
		//	lcdWriteNyble(display, 0x04, true);
			//lcdWriteNyble(display, 0x08, true);
			lcd_SendData(0x14, true, display);
			lcd_SendData(0x0E, true, display);
			lcd_SendData(lcdInstructions::clearScreen, true, display);
			lcd_SendData(0x0C, true, display);


		}
	}
	return init;

}

void lcdWriteNyble(FT_HANDLE& h, byte d, bool rs_)
{

	DWORD sent = 0;
	unsigned char temp;
	temp = ((d << 4) & (byte)(0xF0));
	if (rs_)
	{
		//temp = ((temp | (0x00)) & (LCD_E_OFF));
		temp = (temp & 0b11111110);
		FT_Write((h), (LPVOID)&temp, sizeof(temp), &sent);
		wait(1); //delay de 1 ms
		temp = (temp | (LCD_E_ON));
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);//delay de 3ms.
		temp = temp & (0b11111110);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);

	}
	else
	{

		temp = (temp | (0x02)) & (0b11111110);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);//delay de 1 ms
		sent = 0;
		temp = temp | (LCD_E_ON);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);//delay de 3ms.
		sent = 0;
		temp = temp & (0b11111110);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);
	}



	//byte rs = (rs_ ? 0x00 : 0x02);
	//byte temp =( d << 4 ) & 0xf0;

	//DWORD BytesSent = 0;

	////Bajar enable 
	//temp = (temp | rs) & ~ENABLE;
	//FT_Write(h,(LPVOID) temp, sizeof(temp), &BytesSent);	// D7 D6 D5 D4 XX RS E
	//														//	  |_____d_____|			
	//wait(0.5);
	////Subir enable
	//temp = temp | ENABLE;
	//FT_Write(h, (LPVOID)temp, sizeof(temp), &BytesSent);
	//wait(3);
	////Bajar enable
	//temp = temp & ~ENABLE;
	//FT_Write(h, (LPVOID)temp, sizeof(temp), &BytesSent);
	
}

void wait(float ms)
{
	Timer time;

	do {
		time.stop();
	} while (time.getTime() <= ms);
}
