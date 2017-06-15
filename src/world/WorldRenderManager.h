#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "../engine/VideoDriver.h"
#include "../characters/Player.h"
#include "../characters/Ghost.h"
#include "../characters/Bullet.h"
#include "Tile.h"
#include "Pickup.h"
#include "WorldMath.h"

namespace World {
    
class WorldRenderManager {
public:
    
    void renderMap( Engine::VideoDriver* videoDriver, 
                    Player* player, std::vector<Ghost*>* ghosts,
                    std::vector<Tile>* map );
    void renderPickups( Engine::VideoDriver* videoDriver, std::vector<Pickup*>* pickups );
    void renderBullets( Engine::VideoDriver* videoDriver, std::vector<Bullet*>* bullets );
    
private:
    void renderTile( Engine::VideoDriver* videoDriver,
                     std::vector<Tile>* map,
                     Player* player, std::vector<Ghost*>* ghosts, 
                     int tileIndex, 
                     int tileIsoX, int tileIsoY );
    
    WorldMath worldMath;
};

}


