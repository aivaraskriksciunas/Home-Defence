#pragma once
#include <vector>
#include <fstream>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"
#include "../characters/Player.h"
#include "../characters/Ghost.h"
#include "Tile.h"
#include "Pickup.h"
#include "WorldRenderManager.h"
#include "WorldMath.h"

#define MIN_DISTANCE_BETWEEN_STATIONS 20
#define MAX_LINE_LENGTH 10

namespace World {

class WorldManager
{
public:
    void GenerateMap( std::string path );
    
    void draw( Engine::VideoDriver* videoDriver );
    
    int getStartPosX();
    int getStartPosY();
    
    
    
    //character functions
    void movePlayer( int direction );
    //checks if there are enough enemies based on game time,
    //also calls moveEnemies Function
    void updateEnemies();
    //move and check if bullets have collided with any ghosts
    void updateBullets();
    
    int getPlayerX();
    int getPlayerY();
    int getPlayerHealth();
    void setPlayerHealth( int value );
    bool validateCharacterCoords( int x, int y );
    
    void shoot( int direction );
    //fix wall the player is currently on
    bool fixWall();
    
private:
    std::vector<Tile> map;
    
    WorldRenderManager worldDrawManager;
    WorldMath worldMath;
    
    //player starting positions
    int startPosX, startPosY;
    
    //characters
    Player* player;
    std::vector<Ghost*> ghosts;
    
    //bullets
    std::vector<Bullet*> bullets;
    
    //pickups
    std::vector<Pickup*> pickups;
    
    void orientWalls();
    void resetTileWalls( int index );
    bool hasWalls( int index );
    
    //returns tile type at the given isometric position,
    //I'd place it in WorldMath, but it requires access to map
    int getTileIndexAtIsoPos( int isoX, int isoY );
    
    //checks if the neighbor tile has a wall. Used in orientWalls() function
    //takes the current tile index, neighbor direction (e.g. -1, 0)
    bool isNeighborWall( int currentIndex, int neighborDirectionX, int neighborDirectionY );
    //similar to isNeighborWall(), except it checks whether the neighbor tile is the right type
    bool validateNeighborTile( int currentIndex, int neighborDirectionX, int neighborDirectionY, int tileType );
    
    void handleGhostWallCollision( int ghostX, int ghostY );
    
    void moveEnemies();
    
    void createPickup( int posx, int posy );
    void checkPlayerPickupCollision();
    
};

}



