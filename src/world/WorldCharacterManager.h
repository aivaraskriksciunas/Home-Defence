#pragma once

#include <vector>
#include "../characters/Bullet.h"
#include "../characters/Ghost.h"
#include "../characters/Player.h"
#include "../characters/Gem.h"
#include "Pickup.h"
#include "WorldMath.h"
#include "../characters/Defence.h"
#include "../characters/defences/PlasmaGun.h"

namespace World {
class WorldCharacterManager {
public:
    WorldCharacterManager( WorldMath* worldMathPtr );
    
    void updateBullets( );
    void shoot( int direction, int playerX, int playerY );
    
    void createPickup( int posx, int posy );
    void checkPlayerPickupCollision( int playerX, int playerY );
    
    std::vector<Bullet*>* getBulletsPtr();
    std::vector<Pickup*>* getPickupsPtr();
    std::vector<Ghost*>* getGhostsPtr();
    std::vector<Defence>* getDefencesPtr();
    Gem* getGemPtr();
    
    void clearPickups();
    void clearBullets();
    void clearGhosts();
    
    void moveEnemies( std::vector<Tile>* map, Player* player );
    void createEnemy();
    
    void createGem( int gemX, int gemY );
    void updateGem();
    
    bool createDefence( int posx, int posy, int type );
    void updateDefences();
    
    bool validateCharacterCoords( std::vector<Tile>* map, int x, int y );
    
    int getGhostCount();
    int getGemHealth();
    
private:
    std::vector<Ghost*> ghosts;
    Gem* gem;
    
    //bullets
    std::vector<Bullet*> bullets;
    
    //pickups
    std::vector<Pickup*> pickups;
    
    std::vector<Defence> defences;
    
    WorldMath* worldMathPtr;
     
    //are there any ghosts hitting the gem
    //using this var ensures that no matter how many ghosts are near the gem,
    //it will take the same amount of damage
    bool gemTakingDamage = false;
    
    
    void handleGhostWallCollision( std::vector<Tile>* tile, int ghostX, int ghostY );
    
    int getClosestGhostDirection( int posx, int posy );
};

}
