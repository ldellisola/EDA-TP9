#pragma once


typedef unsigned char byte;

#define NOT(a,b) (-a & b)

namespace lcdInstructions {
	const byte clearScreen =			0x01;
	const byte returnHome=				0x02;
	const byte entryModeSet =			0x04;
	const byte displayOnOffControl =	0x08;

	namespace DisplayControl {
		const byte displayOnOff =		0x04;
		const byte cursorOnOff =		0x02;
		const byte blinkOnOff =			0x01;
	};
	const byte cursorDisplayShift =		0x10;
	const byte funcionSet =				0x20;
	namespace funcionChs {
		const byte dataLenght =			0x10;
		const byte displayLines =		0x08;
		const byte font =				0x04;

	};


};
