#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "../engine/VideoDriver.h"
#include "../characters/Player.h"
#include "../characters/Ghost.h"
#include "../characters/Bullet.h"
#include "../characters/Gem.h"
#include "../characters/Defence.h"
#include "Tile.h"
#include "Pickup.h"
#include "WorldMath.h"

namespace World {
    
class WorldRenderManager {
public:
    
    void renderMap( Engine::VideoDriver* videoDriver, 
                    Player* player, Gem* gem, 
                    std::vector<Ghost*>* ghosts,
                    std::vector<Defence>* defences,
                    std::vector<Tile>* map,
                    int selectedTile = -1 );
    void renderPickups( Engine::VideoDriver* videoDriver, std::vector<Pickup*>* pickups );
    void renderBullets( Engine::VideoDriver* videoDriver, std::vector<Bullet*>* bullets );
    
private:
    void renderTile( Engine::VideoDriver* videoDriver,
                     std::vector<Tile>* map,
                     Player* player, Gem* gem,
                     std::vector<Ghost*>* ghosts, 
                     std::vector<Defence>* defences,
                     int tileIndex, 
                     int tileIsoX, int tileIsoY,
                     bool tileSelected );
    
    WorldMath worldMath;
    
    const sf::Color selectedTileColor = sf::Color( 200, 200, 200, 255 );
    
    void getWallOrientations( int& wallHor, int& wallVert, int damagePercentage ); 
};

}


