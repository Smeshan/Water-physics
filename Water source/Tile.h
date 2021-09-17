#pragma once

#include "Defines.h"
#include "Functions.h"

class Tile {
public:
	Tile(const int x, const int y, const int terrainHeight)
		: _x(x)
		, _y(y)
		, _terrainHeight(terrainHeight)
		, _waterLevel(0) {
	}

	void increaseWater() {
		if (_waterLevel < MAX_WATER_LEVEL) {
			_waterLevel++;
		}
		draw(this);
	}

	int getPosX() const { return _x; }

	int getPosY() const { return _y; }

	int getWaterLevel() const { return _waterLevel; }

	int getHeight() const { return _terrainHeight; }

private:
	int _x;
	int _y;
	int _terrainHeight;
	int _waterLevel;

	void draw(const Tile* currTile) {
		const int waterLevel = currTile->getWaterLevel();
		setPosToDraw(currTile->getPosX() * 2, currTile->getPosY());
		drawWaterTile(waterLevel);
	}
};

