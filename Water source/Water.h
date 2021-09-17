#pragma once
#include<list>
#include<deque>

#include "Tile.h"
#include "Terrain.h"

class Water {
public:
	Water(const int waterSourceX,
		  const int waterSourceY,
		  const Terrain* terrain);

	void update(bool& isTerrainFull);

	// help debugging function
	void drawPerihpery();

private:
	std::vector<std::vector<Tile*>> _terrainTiles;
	size_t _terrainSize;
	bool _isWaterLeveled;

	std::deque<Tile*> _waterTiles;
	std::list<Tile*> _peripheryTiles;
	size_t _waterLevel;

	void draw(const Tile* waterTile);

	void removeTileFromPeriphery(const Tile* newTile);
	void updatePeriphery(const Tile* newTile);
	Tile* findLowestPerihperyTile();
};

