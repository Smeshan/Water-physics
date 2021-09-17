#include "Defines.h"
#include "Water.h"
#include "Functions.h"

bool isInBounds(const int x, const int y, const int size) {
	if (x < 0) { return false; }
	if (x > size - 1) { return false; }
	if (y < 0) { return false; }
	if (y > size - 1) { return false; }
	return true;
}

void Water::updatePeriphery(const Tile* newWaterTile) {
	removeTileFromPeriphery(newWaterTile);
	const int posX = newWaterTile->getPosX();
	const int posY = newWaterTile->getPosY();
	for (int i = 0; i < DIRECTIONS_COUNT; ++i) {
		const int newTileX = posX + Directions[i][0];
		const int newTileY = posY + Directions[i][1];
		if (!isInBounds(newTileX, newTileY, _terrainSize)) {
			continue;
		}
		Tile* newTile = _terrainTiles[newTileY][newTileX];
		const bool ifNewTileHasNoWater = newTile->getWaterLevel() == 0;
		if (ifNewTileHasNoWater) {
			_peripheryTiles.push_back(newTile);
		}
	}
}

Water::Water(const int waterSourceX,
			 const int waterSourceY,
			 const Terrain* terrain)
	: _terrainTiles(terrain->getTiles())
	, _terrainSize (terrain->getSize())
	, _isWaterLeveled(true)
	, _waterLevel(1) {
	Tile* waterSource = _terrainTiles[waterSourceX][waterSourceY];
	_waterTiles.push_back(waterSource);
	waterSource->increaseWater();
	updatePeriphery(waterSource);
}

void Water::update(bool& isTerrainFull) {
	if (_peripheryTiles.empty()) {
		isTerrainFull = true;
		setPosToDraw(0,21); //move the cursor
		return;
	}

	Tile* lowerTile = findLowestPerihperyTile();
	if (lowerTile->getHeight() >= _waterLevel) {
		if (_isWaterLeveled) {
		_waterLevel++;
		_isWaterLeveled = false;
		}
		if (_waterTiles.front()->getWaterLevel() == _waterLevel) {
			_isWaterLeveled = true;
			return;
			}
		if (_waterTiles.front()->getWaterLevel() < _waterLevel) {
			_waterTiles.front()->increaseWater();
			_waterTiles.push_back(_waterTiles.front());
			_waterTiles.pop_front();
			return;
		}
		_waterTiles.push_back(_waterTiles.front());
		_waterTiles.pop_front();
		return;
	}
	
	lowerTile->increaseWater();
	_waterTiles.push_back(lowerTile);
	updatePeriphery(lowerTile);
	_waterLevel = 1;
}

// PERIPHERY FUNCTIONS
Tile* Water::findLowestPerihperyTile() {
	// set ptr to value to avoid nullptr result
	Tile* lowestTile = _peripheryTiles.front();
	int lowestHeigth = lowestTile->getHeight();

	for (auto rit = _peripheryTiles.rbegin(); rit != _peripheryTiles.rend(); ++rit) {
		Tile* currTile = *rit;
		const int currHeight = currTile->getHeight();
		if (lowestHeigth >= currHeight) {
			lowestHeigth = currHeight;
			lowestTile = *rit;
		}
	}
	return lowestTile;
}

void Water::removeTileFromPeriphery(const Tile* newTile) {
	auto it = std::find(_peripheryTiles.begin(),
						_peripheryTiles.end(), newTile);
	if (it != _peripheryTiles.end()) {
		_peripheryTiles.remove(*it);
	}
}

// DEBUGGINGS FUNCTIONS
void Water::drawPerihpery() {
	for (const auto tile : _peripheryTiles) {
		setPosToDraw(tile->getPosX() * 2, tile->getPosY());
		printf("\033[38;5;%dm", 226);
		printf("%d", tile->getHeight()); // filler
		printf("\033[m"); // end of color text
	}
}

