#include "WorldManager.h"

using namespace World;

void WorldManager::GenerateMap( std::string path )
{
    std::ifstream ifile( path );
    
    if ( !ifile.is_open() )
    {
        Engine::SignalManager::sendSignal( SIG_RESOURCE_LOAD_ERROR );
    }
    
    int mapSize = 0;
    ifile >> mapSize; //read the size of the map
    
    worldMath.setWorldSize( mapSize, mapSize );
    
    map.resize( mapSize * mapSize );
    
    //set all tiles to default
    for ( int tileIndex = 0; tileIndex < map.size(); tileIndex++ )
    {
        map[tileIndex].tileType = TILE_GRASS;
        map[tileIndex].texture = TEXTURE_GRASS;
    }
    
    //position where building from file will be placed
    int posx = mapSize / 2;
    int posy = mapSize / 2; 
    while ( !ifile.eof() )
    {
        std::string line;
        
        std::getline( ifile, line );
        
        for ( int charIndex = 0; charIndex < line.length(); charIndex++ )
        {
            int index = worldMath.convertPositionToIndex( posx + charIndex, posy );
            
            if ( line[charIndex] == '.' || line[charIndex] == 'o' )
            {
                map[index].texture = TEXTURE_FLOOR;
                map[index].tileType = TILE_FLOOR;
            }
            else if ( line[charIndex] == '|' )
            {
                map[index].texture = TEXTURE_FLOOR;
                map[index].tileType = TEXTURE_FLOOR;
                //place wall on one side of the tile
                //walls will be reoriented later in orientWalls()
                map[index].wallPositions[0] = true;
            }
            
            if ( line[charIndex] == 'o' )
            {
                int startPosCartX = worldMath.convertIndexToX( index ) * TILE_WIDTH / 2;
                int startPosCartY = worldMath.convertIndexToY( index ) * TILE_HEIGHT;
                int startPosIsoX, startPosIsoY;
                worldMath.convertCartToIso( this->startPosX, this->startPosY, 
                                            startPosCartX, startPosCartY );
            }
        }
        
        posy++;
        
    }
    
    ifile.close();
    orientWalls();
    
    this->player = new Player( this->startPosX, this->startPosY );
    this->ghosts.clear();
    this->pickups.clear();
    this->bullets.clear();
}

void WorldManager::orientWalls()
{
    for ( int y = 0; y < worldMath.getTilesYCount(); y++ )
    {
        for ( int x = 0; x < worldMath.getTilesXCount(); x++ )
        {
            int index = worldMath.convertPositionToIndex( x, y );
            if ( isNeighborWall( index, 0, 0 ) )
            {
                resetTileWalls( index );
                
                int currentTileType = map[index].tileType;
                
                //check for corners
                if ( isNeighborWall( index, -1, 0 ) && 
                     isNeighborWall( index, 0, 1 ) )
                {
                    map[index].wallPositions[WALL_POS_N] = true;
                    map[index].wallPositions[WALL_POS_E] = true;
                }
                else if ( isNeighborWall( index, -1, 0 ) && 
                          isNeighborWall( index, 0, -1 ) )
                {
                    map[index].wallPositions[WALL_POS_S] = true;
                    map[index].wallPositions[WALL_POS_E] = true;
                }
                else if ( isNeighborWall( index, 1, 0 ) && 
                          isNeighborWall( index, 0, 1 ) )
                {
                    map[index].wallPositions[WALL_POS_N] = true;
                    map[index].wallPositions[WALL_POS_W] = true;
                }
                else if ( isNeighborWall( index, 1, 0 ) && 
                          isNeighborWall( index, 0, -1 ) )
                {
                    map[index].wallPositions[WALL_POS_S] = true;
                    map[index].wallPositions[WALL_POS_W] = true;
                }
                
                //check whether the wall is an outside wall, and place it accordingly
                if ( validateNeighborTile( index, 1, 0, currentTileType ) && 
                     !validateNeighborTile( index, -1, 0, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_W] = true;
                }
                else if ( !validateNeighborTile( index, 1, 0, currentTileType ) && 
                          validateNeighborTile( index, -1, 0, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_E] = true;
                }
                
                if ( validateNeighborTile( index, 0, 1, currentTileType ) && 
                     !validateNeighborTile( index, 0, -1, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_N] = true;
                }
                else if ( !validateNeighborTile( index, 0, 1, currentTileType ) && 
                          validateNeighborTile( index, 0, -1, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_S] = true;
                }
            }
            
        }
    }
}

int WorldManager::getTileIndexAtIsoPos( int isoX, int isoY )
{
    for ( int index = 0; index < map.size(); index++ )
    {
        if ( worldMath.isPosInsideTile( index, isoX, isoY ) )
        {
            return index;
        }
    }
    
    return -1;
}

bool WorldManager::hasWalls( int index )
{
    return map[index].wallPositions[0] | 
           map[index].wallPositions[1] |
           map[index].wallPositions[2] |
           map[index].wallPositions[3];
}

void WorldManager::resetTileWalls( int index )
{
    for ( int side = 0; side < WALL_POS_TOTAL; side++ )
    {
        map[index].wallPositions[side] = false;
    }
}

bool WorldManager::isNeighborWall( int currentIndex, int neighborDirectionX, int neighborDirectionY )
{
    int neighborX = worldMath.convertIndexToX( currentIndex ) + neighborDirectionX;
    int neighborY = worldMath.convertIndexToY( currentIndex ) + neighborDirectionY;
    //first check if such a tile exists
    if ( neighborX < 0 || neighborX > worldMath.getTilesXCount() )
    {
        return false;
    }
    
    if ( neighborY < 0 || neighborY > worldMath.getTilesYCount() )
    {
        return false;
    }
    
    //now check if it has a wall
    for ( int side = 0; side < 4; side++ )
    {
        if ( map[worldMath.convertPositionToIndex( neighborX, neighborY )].wallPositions[side] == true )
            return true;
    }
     
    return false;
}

bool WorldManager::validateNeighborTile( int currentIndex, int neighborDirectionX, int neighborDirectionY, int tileType )
{
    int neighborX = worldMath.convertIndexToX( currentIndex ) + neighborDirectionX;
    int neighborY = worldMath.convertIndexToY( currentIndex ) + neighborDirectionY;
    //first check if such a tile exists
    if ( neighborX < 0 || neighborX > worldMath.getTilesXCount() )
    {
        return false;
    }
    
    if ( neighborY < 0 || neighborY > worldMath.getTilesYCount() )
    {
        return false;
    }
    
    //now check if it is the correct type
    return map[worldMath.convertPositionToIndex( neighborX, neighborY )].tileType == tileType;
}

void WorldManager::draw( Engine::VideoDriver* videoDriver )
{
    worldDrawManager.renderMap( videoDriver, player, &ghosts, &map );
    worldDrawManager.renderPickups( videoDriver, &pickups );
    worldDrawManager.renderBullets( videoDriver, &bullets );
}

int WorldManager::getStartPosX()
{
    return this->startPosX;
}

int WorldManager::getStartPosY()
{
    return this->startPosY;
}

//character functions
void WorldManager::movePlayer( int direction )
{
    int newPlayerX, newPlayerY;
    this->player->setDirection( direction );
    this->player->move( newPlayerX, newPlayerY );
    
    //check if the new coordinates are not wall or empty tile
    if ( validateCharacterCoords( newPlayerX, newPlayerY + CHARACTER_HEIGHT ) &&
         validateCharacterCoords( newPlayerX + CHARACTER_WIDTH, newPlayerY + CHARACTER_HEIGHT ) )
    {
        this->player->setPosition( newPlayerX, newPlayerY );
    }
    
    checkPlayerPickupCollision();
}

void WorldManager::moveEnemies()
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
        if ( ghosts[ghost]->checkCollision( player->getX() + CHARACTER_WIDTH / 2, 
                                            player->getY() + CHARACTER_HEIGHT / 2 ) )
        {
            player->takeDamage( 1 );
            //check if player is dead
            if ( player->getHealth() <= 0 )
            {
                Engine::SignalManager::sendSignal( SIG_PLAYER_DEAD );
                return;
            }
        }
        
        float ghostX, ghostY;
        ghosts[ghost]->move( player->getX() - ghosts[ghost]->getX(), //get the difference between player and ghost
                             player->getY() - ghosts[ghost]->getY(),
                             ghostX, ghostY );
        
        if ( validateCharacterCoords( ghostX, ghostY + CHARACTER_HEIGHT ) && 
             validateCharacterCoords( ghostX + CHARACTER_WIDTH, ghostY + CHARACTER_HEIGHT ) )
        {
            ghosts[ghost]->setPosition( ghostX, ghostY );
        }
        else
        {
            handleGhostWallCollision( ghostX, ghostY + CHARACTER_HEIGHT );
            handleGhostWallCollision( ghostX + CHARACTER_WIDTH, ghostY + CHARACTER_HEIGHT );
        }
    }
}

void WorldManager::updateEnemies()
{
    if ( ghosts.size() < 50 )
    {
        createEnemy();
    }
    
    moveEnemies();
}

void WorldManager::createEnemy()
{
    //decide at which edge to place the ghost 
    int edge = rand() % 5;
    
    int spawnIndex = 0;
    switch ( edge )
    {
    case 0:
        //generate random pos on north edge
        spawnIndex = worldMath.convertPositionToIndex( rand() % worldMath.getTilesXCount(), 0 );
        break;
    case 1:
        //generate random pos on east edge
        spawnIndex = worldMath.convertPositionToIndex( worldMath.getTilesXCount() - 1, 
                                                       rand() % worldMath.getTilesYCount() );
        break;
    case 2:
        //generate random pos on south edge
        spawnIndex = worldMath.convertPositionToIndex( rand() % worldMath.getTilesXCount(), 
                                                       worldMath.getTilesYCount() - 1 );
        break;
    case 3:
        //generate random pos on west edge
        spawnIndex = worldMath.convertPositionToIndex( 0, rand() % worldMath.getTilesYCount() );
        break;
    }
    
    int posx, posy;
    worldMath.convertIndexToIso( posx, posy, spawnIndex );
    
    ghosts.push_back( new Ghost( posx, posy ) );
    
}

int WorldManager::getPlayerX()
{
    return this->player->getX();
}

int WorldManager::getPlayerY()
{
    return this->player->getY();
}

int WorldManager::getPlayerHealth()
{
    return this->player->getHealth();
}

void WorldManager::setPlayerHealth( int value )
{
    this->player->setHealth( value );
}

bool WorldManager::validateCharacterCoords( int x, int y )
{
    int currentTile = getTileIndexAtIsoPos( x , y );
    if ( currentTile == -1 )
    {
        return false;
    }
    
    //get character position on tile (N, E, S, W)
    int characterPositionOnTile = worldMath.getCharacterPositionOnTile( currentTile, x, y );
    
    //check if there is a wall on the side where player is located
    if ( map[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( worldMath.isCharacterOnEdge( currentTile, x, y ) )
            return false;
    }
    return true;
}

void WorldManager::handleGhostWallCollision( int ghostX, int ghostY )
{
    int currentTile = getTileIndexAtIsoPos( ghostX, ghostY );
    if ( currentTile == -1 )
    {
        return;
    }
    
    //get character position on tile (N, E, S, W)
    int characterPositionOnTile = worldMath.getCharacterPositionOnTile( currentTile, ghostX, ghostY );
    
    //check if there is a wall on the side where player is located
    if ( map[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( worldMath.isCharacterOnEdge( currentTile, ghostX, ghostY ) )
            map[currentTile].wallHealth--;
    }
    
    //check if walls have been destroyed;
    if ( map[currentTile].wallHealth <= 0 )
    {
        resetTileWalls( currentTile );
    }
}

void WorldManager::shoot( int direction )
{
    bullets.push_back( new Bullet( player->getX(), player->getY(), direction ) );
}

void WorldManager::updateBullets()
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
        }
    }
}

bool WorldManager::fixWall()
{
    int playerIndex = getTileIndexAtIsoPos( player->getX() + CHARACTER_WIDTH / 2, 
                                                      player->getY() + CHARACTER_HEIGHT );
    
    if ( hasWalls( playerIndex ) )
    {
        if ( map[playerIndex].wallHealth < 100 )
        { 
            map[playerIndex].wallHealth = 100;
            return true;
        }
    }
    
    return false;
    
}

void WorldManager::createPickup( int posx, int posy )
{
    //first decide whether or not to create a pickup
    int createPickup = rand() % 4;
    if ( createPickup == 0 )
    {
        pickups.push_back( new Pickup( posx, posy ) );
    }
}

void WorldManager::checkPlayerPickupCollision()
{
    for ( int pickupIndex = 0; pickupIndex < pickups.size(); pickupIndex++ )
    {
        if ( pickups[pickupIndex]->checkForCollision( player->getX(), player->getY() ) )
        {
            pickups.erase( pickups.begin() + pickupIndex );
        }
    }
}