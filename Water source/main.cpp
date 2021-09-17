#include <iostream>
#include <chrono>
#include <thread>

#include "Water.h"
#include "Defines.h"


int main()
{
    Terrain terrain(20, 20);
    
    printf("Choose map(from 1 to 3): ");
    std::string mapNumber;
    std::cin >> mapNumber;
    terrain.loadTerrainFromFile("map_" + mapNumber + ".txt");
    terrain.draw();

    Water water(5, 10, &terrain);
    
    bool isTerrainFull = false;

    while (!isTerrainFull) {
        water.update(isTerrainFull);
        //water.drawPerihpery(); // for debugging
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

    }
    return 0;
}

