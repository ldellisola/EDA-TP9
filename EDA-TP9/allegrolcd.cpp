#include "allegrolcd.h"
#define endFirstLine 16
#define endSecondLine 32


allegrolcd::allegrolcd(double W, double H)
{
	this->error = false;
	if (al_init())
	{
		if (al_install_audio())
		{
			if (al_init_acodec_addon())
			{
				if ((al_reserve_samples(1)))
				{
					if (al_init_image_addon())
					{
						if ((ev_queue = al_create_event_queue()))
						{
							if ((display = al_create_display(1700, 400)))
							{
								al_init_primitives_addon();
								al_init_acodec_addon();
								al_init_font_addon();
								al_init_ttf_addon();
								al_register_event_source(this->ev_queue, al_get_display_event_source(this->display));

							}
							else this->error = true;
						}
						else this->error = true;
					}
					else this->error = true;
				}
				else this->error = true;
			}
			else this->error = true;
		}
		else this->error = true;
	}
	else this->error = true;
	this->cadd = 1;
}


allegrolcd::~allegrolcd()
{
	al_destroy_display(display);
	al_stop_samples();
	al_destroy_sample(music);
	al_destroy_event_queue(ev_queue);
	al_shutdown_image_addon();
	al_uninstall_audio();
}


bool allegrolcd::lcdInitOk() {
	if (this->error == true)
		return 0;
	else return 1;
}
bool allegrolcd::lcdGetError() {
	return this->error;
}
bool allegrolcd::lcdClear() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(50, 50, 1650, 350, al_map_rgb(95, 171, 65));
	al_flip_display();
	return this->error;
}
bool allegrolcd::lcdClearToEOL() {
	if (this->cadd <= endFirstLine)
		al_draw_filled_rectangle(100, 100, 600, 200, al_map_rgb(95, 171, 65));
	return this->error;
}
basicLCD& allegrolcd::operator<<(const char c) {
	WrittenBox text((this->cadd <= endFirstLine ? (50 + (cadd - 1) * 100.0) : (50 + ((cadd - 1) - endFirstLine) * 100.0)), (this->cadd <= endFirstLine) ? (50) : (50 + 100.0), 100.0, 100.0, 50, "", (const char *)FONTPATH, "hotpink",c);
	text.draw();
	al_flip_display();
	this->cadd++;
	return *this;
}
basicLCD& allegrolcd::operator<<(const char * c) {
	int i=0;
	while (c[i])
	{
		if (cadd != endSecondLine + 1)
		{
			WrittenBox text((this->cadd <= endFirstLine ? (50 + (cadd - 1) * 100.0) : (50 + ((cadd - 1) - endFirstLine) * 100.0)), (this->cadd <= endFirstLine) ? (50) : (50 + 100.0), 100.0, 100.0, 50, "", (const char *)FONTPATH, "hotpink",c[i]);
			text.draw();
			this->cadd++;
		}
		else
		{
			cadd = 1;
		}
		c++;
	}
	al_flip_display();
	return *this;
}
basicLCD& allegrolcd::operator<<(std::string str) {
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (cadd != endSecondLine + 1)
		{
			WrittenBox text((this->cadd <= endFirstLine ? (50 + (cadd -1) * 100.0) : (50 + ((cadd - 1) - endFirstLine) * 100.0)), (this->cadd <= endFirstLine) ? (50) : (50 + 100.0), 100.0, 100.0, 50, "", (const char *)FONTPATH, "white",str[i]);
			text.draw();
			this->cadd++;
		}
		else
		{
			this->lcdClear();
			cadd = 1;
		}
	}
	al_flip_display();
	return *this;
}
bool allegrolcd::lcdMoveCursorUp() {
	if (cadd > endFirstLine){
		this->cadd -= endFirstLine;
	}//muevo para arriba
	return true;
}
bool allegrolcd::lcdMoveCursorDown() {
	if (cadd < endFirstLine)
		this->cadd += endFirstLine;
	return true;
}
bool allegrolcd::lcdMoveCursorRight() {
	cursorPosition newpos;
	if (cadd < endFirstLine && cadd>0)
	{
		newpos.column = cadd +1;
		newpos.row = 1;
	}
	else if (cadd == endFirstLine)
	{
		newpos.column = 1;
		newpos.row = 2;
	}
	else if (cadd > endFirstLine && cadd < endSecondLine)
	{
		newpos.row = 2;
		newpos.column = cadd - endFirstLine +1;
	}
	this->lcdSetCursorPosition(newpos);
return true;
}
bool allegrolcd::lcdMoveCursorLeft() {
	cursorPosition newpos;
	if (cadd <= endFirstLine && cadd>1)
	{
		newpos.column = cadd -1;
		newpos.row = 1;
	}
	else if (cadd == endFirstLine+1)
	{
		newpos.column = endFirstLine;
		newpos.row = 1;
	}
	else if (cadd > endFirstLine+1 && cadd <= endSecondLine)
	{
		newpos.row = 2;
		newpos.column = cadd - endFirstLine -1;
	}
	this->lcdSetCursorPosition(newpos);
	return true;
}
bool allegrolcd::lcdSetCursorPosition(const cursorPosition pos) {
	switch (pos.row) {
	case 1:cadd = pos.column; break;
	case 2: cadd = pos.column + endFirstLine; break;
	}
	//lcdUpdateCursor();
	return true;

}
cursorPosition allegrolcd::lcdGetCursorPosition() {
	cursorPosition currpos;
	currpos.column = cadd;
	currpos.row = cadd;
	return currpos;
}

void allegrolcd::lcdUpdateCursor() {}