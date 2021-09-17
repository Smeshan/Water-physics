#pragma once
#include <string>

#define ClearScreen system("cls"); // windows
//#define CLRSCR system("clear"); // linux

// CONSTANTS
const int MIN_WATER_LEVEL = 1;
const int MAX_WATER_LEVEL = 9;
const int DIRECTIONS_COUNT = 8;

const char TEXTURE = char(219);

namespace Colors {
	const int terrain[10] { 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };
	const int water[10] { 26, 33, 27, 21, 12, 20, 19, 18, 4, 17 };
}

// DIRECTIONS
const int Directions[8][2]{
	{-1, -1}, { 0, -1}, { 1, -1}, {-1,  0}, { 1,  0}, {-1,  1}, { 0,  1}, { 1,  1}
};