#pragma once
#include "BasicLcd.h"
#include <allegro5/allegro5.h> 
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "WrittenBox.h"
#define BACKGROUNDPATH "Utils/background.jpg"
#define MUSICPATH "Music/Antman.wav"
#define TUTOPATH "Utils/tuto.jpg"
#define FONTPATH "Triforce.ttf"

class allegrolcd :
	public basicLCD
{
public:
	allegrolcd(double W, double H);
	~allegrolcd();
	bool lcdInitOk();
	bool lcdGetError();
	bool lcdClear();
	bool lcdClearToEOL() ;
	basicLCD& operator<<(const char c);
	basicLCD& operator<<(const char * c) ;
	basicLCD& operator<<(std::string str);
	bool lcdMoveCursorUp();
	bool lcdMoveCursorDown();
	bool lcdMoveCursorRight();
	bool lcdMoveCursorLeft();
	bool lcdSetCursorPosition(const cursorPosition pos);
	cursorPosition lcdGetCursorPosition();
	void lcdUpdateCursor();
private :
	ALLEGRO_FONT * font;
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_EVENT_QUEUE * ev_queue = NULL;
	

};
