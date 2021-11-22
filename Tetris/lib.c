#include "tetris.h"

void gotoxy(int row, int column) {
	static HANDLE h = NULL;
	COORD c = { column, row };

	if (!h) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);

}

int timeCheck(int timeValue) {
	static unsigned int oldTime;
	unsigned int  newTime;

	newTime = GetTickCount64();
	if ((newTime - oldTime) >= timeValue) {
		oldTime = newTime;
		return TRUE;
	}
	
	return FALSE;

}