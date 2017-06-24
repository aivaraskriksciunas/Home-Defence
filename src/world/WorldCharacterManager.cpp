#include "WorldCharacterManager.h"

using namespace World;

WorldCharacterManager::WorldCharacterManager( WorldMath* worldMathPtr )
{
    this->worldMathPtr = worldMathPtr;
}

void WorldCharacterManager::shoot( int direction, int playerX, int playerY )
{
    bullets.push_back( new Bullet( playerX, playerY, direction ) );
}

void WorldCharacterManager::updateBullets()
{
    for ( int bulletIndex = 0; bulletIndex < bullets.size(); bulletIndex++ )
    {
        bullets[bulletIndex]->move();
        
        if ( bullets[bulletIndex]->isDead() )
        {
            bullets.erase( bullets.begin() + bulletIndex );
            continue;
        }
        
        int ghostHit = bullets[bulletIndex]->checkCollisionWithGhost( &ghosts );
        if ( ghostHit != -1 )
        {
            ghosts[ghostHit]->takeDamage( bullets[bulletIndex]->getDamage() );
            bullets.erase( bullets.begin() + bulletIndex );
            Engine::SignalManager::sendSignal( SIG_GHOST_KILLED );
        }
    }
}


void WorldCharacterManager::createPickup( int posx, int posy )
{
    //first decide whether or not to create a pickup
    int createPickup = rand() % 4;
    if ( createPickup == 0 )
    {
        pickups.push_back( new Pickup( posx, posy ) );
    }
}

void WorldCharacterManager::checkPlayerPickupCollision( int playerX, int playerY )
{
    for ( int pickupIndex = 0; pickupIndex < pickups.size(); pickupIndex++ )
    {
        if ( pickups[pickupIndex]->checkForCollision( playerX, playerY ) )
        {
            pickups.erase( pickups.begin() + pickupIndex );
        }
    }
}

std::vector<Bullet*>* WorldCharacterManager::getBulletsPtr()
{
    return &this->bullets;
}

std::vector<Pickup*>* WorldCharacterManager::getPickupsPtr()
{
    return &this->pickups;
}

std::vector<Ghost*>* WorldCharacterManager::getGhostsPtr()
{
    return &this->ghosts;
}

Gem* WorldCharacterManager::getGemPtr()
{
    return this->gem;
}

void WorldCharacterManager::clearPickups() 
{
    this->pickups.clear();
}

void WorldCharacterManager::clearBullets()
{
    this->bullets.clear();
}

void WorldCharacterManager::clearGhosts()
{
    this->ghosts.clear();
}

int WorldCharacterManager::getGemHealth()
{
    this->gem->getHealth();
}

void WorldCharacterManager::createGem( int gemX, int gemY )
{
    this->gem = new Gem( gemX, gemY ); 
}

int WorldCharacterManager::getGhostCount()
{
    this->ghosts.size();
}

void WorldCharacterManager::moveEnemies( std::vector<Tile>* map, Player* player )
{
    int playerX = player->getX();
    int playerY = player->getY();
    
    for ( int ghost = 0; ghost < ghosts.size(); ghost++ )
    {
        if ( ghosts[ghost]->getHealth() <= 0 )
        {
            createPickup( ghosts[ghost]->getX(), ghosts[ghost]->getY() );
            ghosts.erase( ghosts.begin() + ghost );
            continue;
        }
        
        //check if enemy is hitting the player
        if ( ghosts[ghost]->checkCollision( playerX + CHARACTER_WIDTH / 2, 
                                            playerY + CHARACTER_HEIGHT / 2 ) )
        {
            player->takeDamage( 1 );
            //check if player is dead
            if ( player->getHealth() <= 0 )
            {
                Engine::SignalManager::sendSignal( SIG_PLAYER_DEAD );
                return;
            }
        }
        //check if ghost is hitting the gem
        else if ( gem->hasCollided( ghosts[ghost]->getX() + CHARACTER_WIDTH / 2,
                                    ghosts[ghost]->getY() + CHARACTER_HEIGHT / 2 ) )
        {
            this->gemTakingDamage = true;
        }
        
        //get position of the closest target
        int targetX, targetY;
        worldMathPtr->getClosestTargetPos( ghosts[ghost]->getX(), ghosts[ghost]->getY(),
                                       targetX, targetY,
                                       player, gem );
        
        float ghostX, ghostY;
        ghosts[ghost]->move( targetX - ghosts[ghost]->getX(), //get the difference between player and ghost
                             targetY - ghosts[ghost]->getY(),
                             ghostX, ghostY );
        
        if ( validateCharacterCoords( map, ghostX, ghostY + CHARACTER_HEIGHT ) && 
             validateCharacterCoords( map, ghostX + CHARACTER_WIDTH, ghostY + CHARACTER_HEIGHT ) )
        {
            ghosts[ghost]->setPosition( ghostX, ghostY );
        }
        else
        {
            handleGhostWallCollision( map, ghostX, ghostY + CHARACTER_HEIGHT );
            handleGhostWallCollision( map, ghostX + CHARACTER_WIDTH, ghostY + CHARACTER_HEIGHT );
        }
    }
}

void WorldCharacterManager::updateGem()
{
    if ( gemTakingDamage )
    {
        gem->takeDamage( 1 );
    }
    if ( gem->getHealth() <= 0 ) Engine::SignalManager::sendSignal( SIG_GEM_DESTROYED );
    
    gemTakingDamage = false;

}

void WorldCharacterManager::createEnemy()
{
    //decide at which edge to place the ghost 
    int edge = rand() % 5;
    
    int spawnIndex = 0;
    switch ( edge )
    {
    case 0:
        //generate random pos on north edge
        spawnIndex = worldMathPtr->convertPositionToIndex( rand() % worldMathPtr->getTilesXCount(), 1 );
        break;
    case 1:
        //generate random pos on east edge
        spawnIndex = worldMathPtr->convertPositionToIndex( worldMathPtr->getTilesXCount() - 2, 
                                                       rand() % worldMathPtr->getTilesYCount() );
        break;
    case 2:
        //generate random pos on south edge
        spawnIndex = worldMathPtr->convertPositionToIndex( rand() % worldMathPtr->getTilesXCount(), 
                                                       worldMathPtr->getTilesYCount() - 3 );
        break;
    case 3:
        //generate random pos on west edge
        spawnIndex = worldMathPtr->convertPositionToIndex( 1, rand() % worldMathPtr->getTilesYCount() );
        break;
    }
    
    int posx, posy;
    worldMathPtr->convertIndexToIso( posx, posy, spawnIndex );
    
    ghosts.push_back( new Ghost( posx, posy ) );
    
}

bool WorldCharacterManager::validateCharacterCoords( std::vector<Tile>* map, int x, int y )
{
    int currentTile = worldMathPtr->getTileIndexAtIsoPos( x , y );
    if ( currentTile == -1 )
    {
        return false;
    }
    
    //get character position on tile (N, E, S, W)
    int characterPositionOnTile = worldMathPtr->getCharacterPositionOnTile( currentTile, x, y );
    
    //check if there is a wall on the side where player is located
    if ( (*map)[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( worldMathPtr->isCharacterOnEdge( currentTile, x, y ) )
            return false;
    }
    return true;
}

void WorldCharacterManager::handleGhostWallCollision( std::vector<Tile>* map, int ghostX, int ghostY )
{
    int currentTile = worldMathPtr->getTileIndexAtIsoPos( ghostX, ghostY );
    if ( currentTile == -1 )
    {
        return;
    }
    
    //get character position on tile (N, E, S, W)
    int characterPositionOnTile = worldMathPtr->getCharacterPositionOnTile( currentTile, ghostX, ghostY );
    
    //check if there is a wall on the side where player is located
    if ( (*map)[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( worldMathPtr->isCharacterOnEdge( currentTile, ghostX, ghostY ) )
        {
            (*map)[currentTile].wallHealth--;
            if ( (*map)[currentTile].wallHealth <= 0 )
            {
                (*map)[currentTile].wallPositions[0] = false;
                (*map)[currentTile].wallPositions[1] = false;
                (*map)[currentTile].wallPositions[2] = false;
                (*map)[currentTile].wallPositions[3] = false;
            }
        }
    }
}

bool WorldCharacterManager::createDefence( int posx, int posy, int type )
{
    //make sure it will not overlap any other defences
    for ( int defence = 0; defence < defences.size(); defence++ )
    {
        if ( defences[defence].checkCollision( posx, posy ) )
        {
            return false;
        }
    }
    
    switch ( type )
    {
        case DEFENCE_TYPE_PLASMA_GUN:
            defences.push_back( PlasmaGun( posx, posy ) );
            break;
    }
    
    return true;
}

void WorldCharacterManager::updateDefences()
{
    for ( int defenceIndex = 0; defenceIndex < defences.size(); defenceIndex++ )
    {
        if ( ghosts.size() > 0 ) //only fire when there are ghosts
        {
            if ( defences[defenceIndex].isShooting() )
            {
                int defenceX = defences[defenceIndex].getX();
                int defenceY = defences[defenceIndex].getY();
                bullets.push_back( new Bullet( defenceX, defenceY, 
                                               getClosestGhostDirection( defenceX, defenceY ) ) );
            }
        }
    }
}

int WorldCharacterManager::getClosestGhostDirection( int posx, int posy )
{
    int closestGhostIndex = 0;
    int closestGhostDistance = worldMathPtr->getDistanceBetweenPoints( posx, posy,
                                                                       ghosts[0]->getX(), ghosts[0]->getY() );
    for ( int ghostIndex = 1; ghostIndex < ghosts.size(); ghostIndex++ )
    {
        int currentDistance = worldMathPtr->getDistanceBetweenPoints( posx, posy,
                                                                      ghosts[ghostIndex]->getX(), 
                                                                      ghosts[ghostIndex]->getY() );
        
        if ( currentDistance < closestGhostDistance )
        {
            closestGhostDistance = currentDistance;
            closestGhostIndex = ghostIndex;
        }
    }
    
    int distY = ghosts[closestGhostIndex]->getY() - posy;
    int distX = ghosts[closestGhostIndex]->getX() - posx;
    
    return std::atan2( distY, distX ) * 180 / M_PI;
    
}

std::vector<Defence>* WorldCharacterManager::getDefencesPtr()
{
    return &defences;
}