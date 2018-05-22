#pragma once
#include "masksAnd Stuff.h"
#define FTD2XX_EXPORTS
#include "ftd2xx.h"
#include "Timer.h"

#define LCD_ENABLE_ON 0b00000001
#define LCD_ENABLE_OFF 0b11111110

#define ENABLE 0x01
typedef unsigned long DWORD;

bool initDisplay(const char * displayName, FT_HANDLE& display);

void lcd_SendData(byte data, bool rs, FT_HANDLE& handle);

void lcdWriteNyble(FT_HANDLE & h, byte d, bool rs_);


void wait(float ms);