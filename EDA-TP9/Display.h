#pragma once
#include "masksAnd Stuff.h"
#define FTD2XX_EXPORTS
#include "librerias/ftd2xx.h"
#include "Timer.h"

#define LCD_E_ON 0b00000001
#define LCD_E_OFF 0b00000000

#define ENABLE 0x01
typedef unsigned long DWORD;

FT_HANDLE initDisplay(const char * displayName);

void lcd_SendData(byte data, bool rs, FT_HANDLE& handle);

void lcdWriteNyble(FT_HANDLE & h, byte d);


void wait(float ms);