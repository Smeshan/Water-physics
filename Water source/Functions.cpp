#include <iostream>
#include <windows.h>

#include "Defines.h"
#include "Functions.h"

void setPosToDraw(const int x, const int y) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD newPos = { x, y };
	SetConsoleCursorPosition(output, newPos);
}

void drawTerrainTile(const int colorInt) {
	// convert heigth in color
	printf("\033[38;5;%dm", Colors::terrain[colorInt]);
	printf("%c%c", TEXTURE, TEXTURE); // filler
	//printf("%d%c", colorInt, TEXTURE); // debugger filler
	printf("\033[m"); // end of color text
}

void drawWaterTile(const int colorInt) {
	// convert water level in color
	printf("\033[38;5;%dm", Colors::water[colorInt]);
	printf("%c%c", TEXTURE, TEXTURE); // filler
	//printf("%d%c", colorInt, TEXTURE); // debugger filler
	printf("\033[m"); // end of color text
}