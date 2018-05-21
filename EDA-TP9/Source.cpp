#include "Display.h"
#include <iostream>
#include "hitachilcd.h"
#include "allegrolcd.h"
using namespace std;


int main() {

	//hitachilcd  prog( (char *)"EDA LCD 2 B");
	allegrolcd prog(1.0, 2.0);
	if(prog.lcdInitOk()){
		prog.lcdClear();
		string a = "putito";
		prog << a;
}
	else
		cout << "init not display" << endl;

	cin.get();

	return 1;
}