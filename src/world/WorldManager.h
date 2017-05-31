#pragma once
#include <vector>
#include <fstream>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"
#include "Tile.h"

#define TILE_WIDTH 40
#define TILE_HEIGHT 20

#define MIN_DISTANCE_BETWEEN_STATIONS 20
#define MAX_LINE_LENGTH 10

namespace World {

class WorldManager
{
public:
    void GenerateMap( std::string path );
    void renderMap( Engine::VideoDriver* videoDriver );
    void scrollMap( int scrollX, int scrollY );
    
private:
    std::vector<Tile> map;
    
    //map size in tiles (how many tiles make up each side)
    int tilesXCount, tilesYCount;
    
    //sets map offset, used for scrolling
    int offsetX, offsetY;
    
    void orientWalls();
    
    void convertCartToIso( int& isoX, int& isoY, int cartX, int cartY );
    
    int convertIndexToY( int index );
    int convertIndexToX( int index );
    int convertPositionToIndex( int posx, int posy );
    int getDistanceBetweenTiles( int startTile, int endTile );
    //checks if the neighbor tile is the given tile type.
    //takes the current tile index, neighbor direction (e.g. -1, 0), and neighbor tile type
    bool validateNeighborTile( int currentIndex, int neighborDirectionX, int neighborDirectionY, int tileType );
};

}



