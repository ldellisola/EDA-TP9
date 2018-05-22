#pragma once

#define FTD2XX_EXPORTS
#include "ftd2xx.h"
#include "Timer.h"

//Flag to recieve or not bits info
#define LCD_ENABLE_ON 0x01
#define LCD_ENABLE_OFF 0xFE

// Flag Rs para identificar instruccion o dato
#define RS_INSTRUCTION true								
#define RS_DATA false

//Funcion Clear
#define FUNCIONCLEAR 0x01

//Funcion set y config
#define FUNCIONSET 0x02
#define FUNCIONSET_8BITS (FUNCIONSET | 0x01)
#define FUNCIONSET_4BITS FUNCIONSET
#define FUNSET_2LINES_5X8 ( (FUNCIONSET_4BITS << 4) | 0x08 )		//0x28	 No se por qu� era 0x14 en el programa...		

//Display control con todo set off
#define DISPLAYONOFF 0x0E

//Entry set mode para inicializacion
#define ENTRYMODESET 0x0C

typedef unsigned long DWORD;

/*Secuencia de incializaci�n del lcd*/
bool initDisplay(const char * displayName, FT_HANDLE& display);

/*La funcion lcd_SendData recibe un byte de informaci�n e invoca a lcdWriteNyble enviando el Nyble mas significativo 
en primer lugar y luego el menos significativo, tambien recibe el bool de RS y el puntero a handle para poder enviar al 
lcd la info*/
void lcd_SendData(byte data, bool rs, FT_HANDLE& handle);

/*La funci�n lcdWriteNyble toma la informaci�n del byte y mediante el bool rs_ decide si lo que le lleg� es dato a 
imprimir en pantalla o una instruccion para el lcd */
void lcdWriteNyble(FT_HANDLE & h, byte d, bool rs_);

/*Funci�n esperar...*/
void wait(float ms);