#pragma once
#include <vector>
#include <cmath>
#include "Tile.h"
#include "../characters/Player.h"
#include "../characters/Gem.h"

namespace World {
class WorldMath {
public:
    void setWorldSize( int tilesXCount, int tilesYCount );
    
    int convertIndexToY( int index );
    int convertIndexToX( int index );
    void convertIndexToIso( int& posx, int& posy, int index );
    int convertIsoToIndex( int isoX, int isoY );
    int convertPositionToIndex( int posx, int posy );
    
    int getDistanceBetweenTiles( int startTile, int endTile );
    int getDistanceBetweenPoints( int point1X, int point1Y, int point2X, int point2Y );
    
    void convertCartToIso( int& isoX, int& isoY, int cartX, int cartY );
    void convertIsoToCart( int& cartX, int& cartY, int isoX, int isoY );
    
    int getTilesXCount();
    int getTilesYCount();
    
    //checks if character is on the edge of the tile, where the walls are located
    //used for checking character collision with walls
    bool isCharacterOnEdge( int tileIndex, int posx, int posy );
    //check if the given position is inside the tile
    bool isPosInsideTile( int tileIndex, int posx, int posy );
    
    //returns which side of tile character is located
    int getCharacterPositionOnTile( int index, int isoX, int isoY );
    
    void getClosestTargetPos( int posx, int posy, int& targetPosX, int& targetPosY,
                              Player* player, Gem* gem );
    
    int getTileIndexAtIsoPos( int isoX, int isoY );
    
    float getWallDamagePercentage( Tile* tile );
    
private:
    static int tilesXCount, tilesYCount;
};

}

