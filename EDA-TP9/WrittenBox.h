#pragma once
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_primitives.h>
using namespace std;

class WrittenBox
{
public:
	WrittenBox(double x_, double y_, double width_, double height_, int fontSize_, string text_, const char * fontPath, const char * fontColor, char singles_);
	~WrittenBox();
	void draw();
protected:
	string text;
	char singles;
	ALLEGRO_BITMAP * bitmap;
	ALLEGRO_COLOR fontColor;
	float x;
	float y;
	float width;
	float height;
	ALLEGRO_FONT * font;
};

//
//typedef struct textData
//{
//	float x, y, width, height;
//	int fontSize;
//	string text;
//	const char * path;
//	const char * color;
//};