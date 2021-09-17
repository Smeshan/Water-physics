#include <iostream>
#include <fstream>

#include "Terrain.h"
#include "Functions.h"

Terrain::Terrain(int h, int w)
    : _h(h)
    , _w(w)
    , _size(h) { // square terrain for now
    _tiles.resize(_size);
    for (int i = 0; i < _size; ++i) {
        _tiles[i].resize(_size);
    }
}

void Terrain::loadTerrainFromFile(const std::string fileName) {
    std::fstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Wrong file name: " << fileName << std::endl;
    }
    std::string line;

    for (int y = 0; y < _size; ++y) {
        getline(file, line);
        const size_t lineSize = line.size();
        for (int x = 0; x < lineSize; ++x) {
            // convert ASCII number to int
            const int tileHeigth = line[x] - '0';
            // insert new ptr to tile
            _tiles[y][x] = new Tile(x , y, tileHeigth);
        }
    }
}

std::vector<std::vector<Tile*>> Terrain::getTiles() const {
    return _tiles; //hope RVO will sort this copy
}

Tile* Terrain::getTile(const int x, const int y) const {
    return _tiles[x][y];
}

size_t Terrain::getSize() const {
    return _size;
}

void Terrain::draw() {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            const int tileHeigth = _tiles[i][j]->getHeight();
            setPosToDraw(j * 2, i);
            drawTerrainTile(tileHeigth);
        }
    }
}