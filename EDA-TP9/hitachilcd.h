#pragma once
#define FTD2XX_EXPORTS
#include "librerias\ftd2xx.h"
#include "BasicLcd.h"
#include <string>
#include <iostream>
using namespace std;

class hitachilcd :
	public basicLCD
{
public:
	hitachilcd(char * myDevice);
	virtual ~hitachilcd();
	virtual bool lcdInitOk();
	virtual bool lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const char c);
	virtual basicLCD& operator<<(const char * c);
	virtual basicLCD& operator<<(string str);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();

private:
	bool Init;
	FT_HANDLE  device_handler;
	virtual void lcdUpdateCursor();
	unsigned char Hcadd();
};

#define LCD_SET_DDRAM_ADRESS ((unsigned char)0x80)
#define BEGIN_OF_FIRST_LINE 1
#define END_OF_FIRST_LINE 16
#define BEGIN_OF_SECOND_LINE 17
#define END_OF_SECOND_LINE 32
#define firstLineRange	((cadd >= BEGIN_OF_FIRST_LINE) && (cadd <= END_OF_FIRST_LINE))
#define secondLineRange	((cadd >= BEGIN_OF_SECOND_LINE) && (cadd <= END_OF_SECOND_LINE))
#define totalRange			((cadd >= BEGIN_OF_FIRST_LINE) && (cadd <= END_OF_SECOND_LINE))
#define isOnFirstLine(x) (((x >= BEGIN_OF_FIRST_LINE) && (x <= END_OF_FIRST_LINE)))
#define isOnSecondLine(x) (((x >= BEGIN_OF_SECOND_LINE) && (x <= END_OF_SECOND_LINE)))
#define MIN_ROW 0
#define MAX_ROW 1
#define MIN_COL 0
#define MAX_COL 15
#define CANT_ROW	2
#define CANT_COL	16
#define isValidRow(x) (((x >= MIN_ROW) && (x <= MAX_ROW)))
#define isValidCol(x) (((x >= MIN_COL) && (x <= MAX_COL)))
#define isValidPos(pos) ((isValidRow(pos.row) && isValidCol(pos.column)))
#define HITACHI_OFFSET_SECOND_LINE 0x30
#define ERROR_HCADD 0xFF