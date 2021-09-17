#pragma once
#include <vector>

#include "Tile.h"

class Terrain {
public:

	Terrain(const int h, const int w);

	void loadTerrainFromFile(const std::string fileName);

	std::vector<std::vector<Tile*>> getTiles() const;

	Tile* getTile(const int x, const int y) const;

	size_t getSize() const;

	void draw();

private:
	std::vector<std::vector<Tile*>> _tiles;
	size_t _size;
	int _h;
	int _w;
};

