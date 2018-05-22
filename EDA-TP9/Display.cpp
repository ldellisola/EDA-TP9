#include "Display.h"

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
			//DiplayOnOff config
			lcd_SendData(DISPLAYONOFF, RS_INSTRUCTION, display);	//0x0E
			//limpiar la pantalla
			lcd_SendData(FUNCIONCLEAR, RS_INSTRUCTION, display);
			//Entry mode set
			lcd_SendData(ENTRYMODESET, RS_INSTRUCTION, display);	//0x0C
		}
	}
	return init;
}

void lcd_SendData(byte data, bool rs_, FT_HANDLE& handle)
{
	lcdWriteNyble(handle, data >> 4, rs_);		//mando el nybble mas significativo.
	lcdWriteNyble(handle, data, rs_);			//mando el nybble menos significativo.
}

void lcdWriteNyble(FT_HANDLE& h, byte d, bool rs_)
{
	DWORD sent = 0;
	unsigned char temp;
	temp = ((d << 4) & (byte)(0xF0));
	if (rs_)
	{	//Secuencia de envio de Nybles para la interpretacion de una instruccion del lcd
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
		temp = (temp | (LCD_ENABLE_ON));
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(3);								//delay de 3ms.
		temp = (temp & LCD_ENABLE_OFF);
		FT_Write(h, (LPVOID)&temp, sizeof(temp), &sent);
		wait(1);								//delay de 1 ms
	}
	else
	{	//Idem para un dato
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
