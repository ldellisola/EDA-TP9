#pragma once
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
	FT_HANDLE * device_handler;
	virtual void lcdUpdateCursor();
	unsigned char Hcadd();
};

