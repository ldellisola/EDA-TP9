#pragma once
#include "CursesClass.h"
#include "BasicLcd.h"
#include <fstream>
#include <string>

using namespace std;


void stringMode(CursesClass& curses, basicLCD& display);

void error(CursesClass& curses);

void printInstructions(CursesClass& curses);