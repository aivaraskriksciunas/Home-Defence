#pragma once
#include <vector>
#include <fstream>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"
#include "../characters/Player.h"
#include "../characters/Ghost.h"
#include "../characters/Gem.h"
#include "Tile.h"
#include "Pickup.h"
#include "WorldRenderManager.h"
#include "WorldMath.h"
#include "WorldCharacterManager.h"

#define MIN_DISTANCE_BETWEEN_STATIONS 20
#define MAX_LINE_LENGTH 10

#define FIRST_LEVEL_GHOST_COUNT 6

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
    //if required, take away health from gem
    void updateGem();
    
    int getPlayerX();
    int getPlayerY();
    int getPlayerHealth();
    void setPlayerHealth( int value );
    int getGhostCount();
    
    void shoot( int direction );
    //fix wall the player is currently on
    bool fixWall();
    
    int getGemHealth();
    
    void setCreateMoreEnemies( bool value );
    void calculateLevelEnemyCount( int level );
    
    void clearPickups();
    void clearBullets();
    
    void selectTile( int mouseX, int mouseY );
    
    //builds wall on selected tile
    bool buildWall();
    
private:
    std::vector<Tile> map;
    
    WorldRenderManager worldDrawManager;
    WorldMath worldMath;
    WorldCharacterManager* characterManager;
    
    int levelGhostCount;
    
    Player* player;
    //player starting position
    int startPosX, startPosY;
    
    //whether or not create more enemies
    bool createEnemies = false;
    
    int selectedTile;
    
    void orientWalls();
    void resetTileWalls( int index );
    bool hasWalls( int index );
    
    //checks if the neighbor tile has a wall. Used in orientWalls() function
    //takes the current tile index, neighbor direction (e.g. -1, 0)
    bool isNeighborWall( int currentIndex, int neighborDirectionX, int neighborDirectionY );
    //similar to isNeighborWall(), except it checks whether the neighbor tile is the right type
    bool validateNeighborTile( int currentIndex, int neighborDirectionX, int neighborDirectionY, int tileType );
    
    
    
};

}



