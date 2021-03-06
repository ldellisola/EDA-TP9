#include "hitachilcd.h"
#include "Display.h"
#define FTD2XX_EXPORTS
#include "librerias/ftd2xx.h"
#include <string>
#include <iostream>
using namespace std;



hitachilcd::hitachilcd(char * myDevice)
{
	Init = false;
	error = true;
	initDisplay(myDevice,this->device_handler);		//El arreglo de char es el string que identifica al lcd que estamos utilizando
	if (this->device_handler != nullptr)	//Si el puntero device_handler no es NULL se realiz� correctamente la inicializacion
	{
		this->Init = true;
		error = false;
	}
	cadd = 1;		//cursor posicion
}

bool hitachilcd::lcdInitOk() {

	return this->Init;
}
bool hitachilcd::lcdGetError() {
	bool final = false;
	DWORD * lpdwAmountInRxQueue = NULL;
	DWORD * lpdwAmountInTxQueue = nullptr;
	DWORD * lpdwEventStatus = nullptr;
	FT_STATUS state = FT_GetStatus(device_handler, lpdwAmountInRxQueue, lpdwAmountInTxQueue, lpdwEventStatus);
	if (state == FT_OK) { final = true; }
	else error = true;
	return final;
}
bool hitachilcd::lcdClear() {
	bool result = false;
	FT_STATUS state = FT_OK;
	lcd_SendData(FUNCIONCLEAR, RS_INSTRUCTION, this->device_handler); 
	if (state == FT_OK)
	{
		cadd = 1;
		result = true;
	}
	else error = true;
	return result;
}
bool hitachilcd::lcdClearToEOL() {
	int cadd_2 = this->cadd;
	int limit = 0;
	if (isOnFirstLine(this->cadd))
		limit = END_OF_FIRST_LINE;
	else if (isOnSecondLine(this->cadd))
		limit = END_OF_SECOND_LINE;
	//else this->error = true;//Este caso es que el cursor se fue d ela pantalla
	if (!error)
	{
		while (this->cadd++ <= limit)
			lcd_SendData(' ', RS_DATA, this->device_handler); 
		cadd = cadd_2;
		lcdUpdateCursor();
	}
	return error;				//True si hubo error
}

basicLCD& hitachilcd::operator<<(const char  c) {
	if (cadd == 1)
		lcdClear();
	lcd_SendData(c, RS_DATA, this->device_handler);
	if (++cadd == (END_OF_SECOND_LINE + 1))
	{
		cadd = BEGIN_OF_FIRST_LINE;
	}
	lcdUpdateCursor();
	return *this;
}

basicLCD& hitachilcd::operator<<(const char * c) {
	unsigned long int iterator = 0;
	if (cadd == 1)
		lcdClear();
	while (c[iterator])
	{
		lcd_SendData(c[iterator++], RS_DATA, this->device_handler);
		if (++cadd == END_OF_SECOND_LINE + 1)
		{ 
			this->cadd = BEGIN_OF_FIRST_LINE;
		}
		lcdUpdateCursor();
	}
	return *this;
}

basicLCD& hitachilcd::operator<<(string str) {
	if (cadd == 1)
		lcdClear();
	for (unsigned int iterator = 0; iterator < (str.size()); iterator++)
	{
		lcd_SendData(str[iterator], RS_DATA, this->device_handler);
		if (++cadd == END_OF_SECOND_LINE + 1){
			this->cadd = BEGIN_OF_FIRST_LINE;
		}
		lcdUpdateCursor();
	}
	return *this;
}

bool hitachilcd::lcdMoveCursorUp() {
	if (firstLineRange) { return true; }		//Ya estoy en la primer linea
	else if (secondLineRange) {
		cursorPosition newPos;
		newPos.column = this->cadd - CANT_COL;
		newPos.row =1 ;
		this->lcdSetCursorPosition(newPos);
		return true;
	}
	else return false; //Me fui del display
}

bool hitachilcd::lcdMoveCursorDown() {
	if (firstLineRange) {
		cursorPosition newPos;
		newPos.column = cadd;
		newPos.row = 2;
		lcdSetCursorPosition(newPos);
		return true;
	}
	else
		return true; //no se puede mover hacia abajo
}

bool hitachilcd::lcdMoveCursorRight() {
	if (totalRange && (this->cadd != END_OF_SECOND_LINE))//Siempre que no haya llegado al final
	{
		cursorPosition newPos;
		if (secondLineRange) {
			//Si estoy en la segunda linea
			newPos.row = 2;
			newPos.column = this->cadd - CANT_COL + 1;
		}
		else if (firstLineRange && (this->cadd != END_OF_FIRST_LINE))
		{//Estoy por el medio de la primer linea
			newPos.row = 1;
			newPos.column = cadd + 1;
		}
		else if (this->cadd == END_OF_FIRST_LINE)//Estoy en la primer linea al final
		{
			newPos.row = 2;
			newPos.column = 1;
		}
		lcdSetCursorPosition(newPos);
		return true;
	}
	else return true;//Me pas� de el display
}

bool hitachilcd::lcdMoveCursorLeft() {
	if (totalRange && (this->cadd != 1))
	{
		cursorPosition newPos;
		if (secondLineRange && (this->cadd != BEGIN_OF_SECOND_LINE)){
			//Si estoy en la segunda linea
			newPos.row = 2;
			newPos.column = cadd - CANT_COL - 1;
		}
		else if (firstLineRange)
		{
			newPos.row = 1;
			newPos.column = cadd - 1;
		}
		else if (this->cadd == BEGIN_OF_SECOND_LINE){
			//Voy hacia atras
			newPos.row = 1;
			newPos.column = END_OF_FIRST_LINE;
		}
		lcdSetCursorPosition(newPos);
		return true;
	}
	else return true;//Estoy en el principio
}

bool hitachilcd::lcdSetCursorPosition(const cursorPosition pos) {
	switch (pos.row){
	case 1:cadd = pos.column; break;
	case 2: cadd = pos.column + CANT_COL; break;
	}
	lcdUpdateCursor();
	return true;
}

cursorPosition hitachilcd::lcdGetCursorPosition() {
	cursorPosition currPos;
	if (firstLineRange)
	{
		currPos.row = 1;
		currPos.column = cadd;
	}
	else if (secondLineRange)
	{
		currPos.column = cadd - CANT_COL;
		currPos.row = 2;
	}
	else {
		currPos.column = -1;
		currPos.row = -1;
	}
	return currPos;
}

hitachilcd::~hitachilcd()
{
	if (Init)
		FT_Close(device_handler);
}

void hitachilcd::lcdUpdateCursor()
{
	lcd_SendData(LCD_SET_DDRAM_ADRESS | Hcadd(), RS_INSTRUCTION, this->device_handler);
}

unsigned char hitachilcd::Hcadd()
{
	unsigned char hcad_ = 0;
	if (firstLineRange)
		hcad_ = ((char)cadd) - 1;
	else if (secondLineRange)
	{
		hcad_ = ((char)cadd - 1);
		hcad_ += HITACHI_OFFSET_SECOND_LINE;
	}
	else hcad_ = ERROR_HCADD;

	return hcad_;	
}