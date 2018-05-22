#include "Display.h"
#include <iostream>
using namespace std;

//Funcion Clear
#define FUNCIONCLEAR 0x01

//FUNCION_SET
#define FUNCIONSET_8BITS 0x03
#define FUNCIONSET_4BITS 0x02

#define FUNSET_2LINES_5X8 ((FUNCIONSET_4BITS << 4)| 0x08 )		//0x28	 No se por qué era 0x14 en el programa...		

#define DISPLAYONOFF	

#define RS_INSTRUCTION true								
#define RS_DATA false

bool initDisplay(const char * displayName, FT_HANDLE& display)
{
	bool init = false;
	if (FT_OK == FT_OpenEx((PVOID)displayName, FT_OPEN_BY_DESCRIPTION, &display)) {
		byte allPins = 0xff, asyncMode = 1;
		if (FT_OK == FT_SetBitMode(display, allPins, asyncMode))
		{
			init = true;
			 // Mando 3 veces el modo de 8 bits
			lcdWriteNyble(display, FUNCIONSET_8BITS, RS_INSTRUCTION);
			wait(4);
			lcdWriteNyble(display, FUNCIONSET_8BITS, RS_INSTRUCTION);
			wait(1);
			lcdWriteNyble(display, FUNCIONSET_8BITS, RS_INSTRUCTION);
			 // Mando una vez el modo de 4 bits
			lcdWriteNyble(display, FUNCIONSET_4BITS, RS_INSTRUCTION);
			//A partir de este punto, todo dato o instrucción se recibe de a nybles 
			//Enviamos Funcion set en modo 4 bits, 2 líneas y fuente de 5x8 
			lcd_SendData(FUNSET_2LINES_5X8, RS_INSTRUCTION, display);
			//
			lcd_SendData(0x0E, RS_INSTRUCTION, display);
			lcd_SendData(FUNCIONCLEAR, RS_INSTRUCTION, display);
			lcd_SendData(0x0C, RS_INSTRUCTION, display);
		}
	}
	return init;
}

void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	cout << (data >> 4);
	lcdWriteNyble(handle, data >> 4, rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.
}

void lcdWriteNyble(FT_HANDLE& h, byte d, bool rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	temp = ((d << 4) & (byte)(0xF0));
	if (rs_)
	{
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);								//delay de 3ms.
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
	}
	else
	{
		temp = (temp | (0x02)) & (LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
		sent = 0;
		temp = temp | (LCD_ENABLE_ON);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);								//delay de 3ms.
		sent = 0;
		temp = temp & (LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);
	}
}

void wait(float ms)
{
	Timer time;
	do {
		time.stop();
	} while (time.getTime() <= ms);
}
