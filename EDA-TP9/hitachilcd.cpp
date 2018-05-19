#include "hitachilcd.h"
#include "Display.h"
#include "librerias\ftd2xx.h"

hitachilcd::hitachilcd(char * myDevice)
{
	Init = false;
	error = true;
	this->device_handler = (initDisplay(myDevice));//De esto tampoco estoy muy seguro
	if (this->device_handler != nullptr)
	{
		this->Init = true;
		error = false;
	}
	cadd = 1;
}

bool hitachilcd::lcdInitOk() {

	return this->Init;
}
bool hitachilcd::lcdGetError() {
	bool final = false;
	DWORD * lpdwAmountInRxQueue = NULL;
	DWORD * lpdwAmountInTxQueue = nullptr;
	DWORD * lpdwEventStatus = nullptr;
	FT_STATUS state = FT_GetStatus(*device_handler, lpdwAmountInRxQueue, lpdwAmountInTxQueue, lpdwEventStatus);
	if (state == FT_OK) { final = true; }
	else error = true;
	return final;
}
bool hitachilcd::lcdClear() {
	bool final;
	FT_STATUS state = FT_OK;
	lcdWriteNyble(this->device_handler,) //No se como usarlo
}
bool hitachilcd::lcdClearToEOL() {}
basicLCD& hitachilcd::operator<<(const char c) {}
basicLCD& hitachilcd::operator<<(const char * c) {}
basicLCD& hitachilcd::operator<<(std::string str) {}
bool hitachilcd::lcdMoveCursorUp() {}
bool hitachilcd::lcdMoveCursorDown() {}
bool hitachilcd::lcdMoveCursorRight() {}
bool hitachilcd::lcdMoveCursorLeft() {}
bool hitachilcd::lcdSetCursorPosition(const cursorPosition pos) {}
cursorPosition hitachilcd::lcdGetCursorPosition() {}

hitachilcd::~hitachilcd()
{
	if (Init)
	{
		FT_Close(*device_handler);
		delete device_handler;
	}
}
