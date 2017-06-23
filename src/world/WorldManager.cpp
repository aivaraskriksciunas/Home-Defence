#include "WorldManager.h"

using namespace World;

void WorldManager::GenerateMap( std::string path )
{
    srand( time( 0 ) );
    std::ifstream ifile( path );
    
    if ( !ifile.is_open() )
    {
        Engine::SignalManager::sendSignal( SIG_RESOURCE_LOAD_ERROR );
    }
    
    characterManager = new WorldCharacterManager( &worldMath );
    
    int mapSize = 0;
    ifile >> mapSize; //read the size of the map
    
    worldMath.setWorldSize( mapSize, mapSize );
    
    map.resize( mapSize * mapSize );
    
    //set all tiles to default
    for ( int tileIndex = 0; tileIndex < map.size(); tileIndex++ )
    {
        map[tileIndex].tileType = TILE_GRASS;
        map[tileIndex].texture = TEXTURE_GRASS;
        map[tileIndex].wallHealth = 100;
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
            
            if ( line[charIndex] == '.' || line[charIndex] == 'o' || line[charIndex] == 'g' )
            {
                map[index].texture = TEXTURE_FLOOR;
                map[index].tileType = TILE_FLOOR;
            }
            else if ( line[charIndex] == '|' )
            {
                map[index].texture = TEXTURE_FLOOR;
                map[index].tileType = TILE_FLOOR;
                //place wall on one side of the tile
                //walls will be reoriented later in orientWalls()
                map[index].wallPositions[0] = true;
            }
            
            if ( line[charIndex] == 'o' )
            {
                int startPosCartX = worldMath.convertIndexToX( index ) * TILE_WIDTH / 2;
                int startPosCartY = worldMath.convertIndexToY( index ) * TILE_HEIGHT;
                worldMath.convertCartToIso( startPosX, startPosY, 
                                            startPosCartX, startPosCartY );
            }
            else if ( line[charIndex] == 'g' )
            {
                int gemCartX = worldMath.convertIndexToX( index ) * TILE_WIDTH / 2;
                int gemCartY = worldMath.convertIndexToY( index ) * TILE_HEIGHT;
                int gemIsoX, gemIsoY;
                worldMath.convertCartToIso( gemIsoX, gemIsoY, 
                                            gemCartX, gemCartY );
                
                characterManager->createGem( gemIsoX, gemIsoY );
            }
        }
        
        posy++;
        
    }
    
    ifile.close();
    orientWalls();
    
    this->player = new Player( startPosX, startPosY );
    this->selectedTile = -1;
    characterManager->clearGhosts();
    characterManager->clearPickups();
    characterManager->clearBullets();
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
                if ( !validateNeighborTile( index, 1, 0, currentTileType ) && 
                          validateNeighborTile( index, -1, 0, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_E] = true;
                }
                
                if ( validateNeighborTile( index, 0, 1, currentTileType ) && 
                     !validateNeighborTile( index, 0, -1, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_N] = true;
                }
                if ( !validateNeighborTile( index, 0, 1, currentTileType ) && 
                      validateNeighborTile( index, 0, -1, currentTileType ) )
                {
                    map[index].wallPositions[WALL_POS_S] = true;
                }
            }
            
        }
    }
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
    worldDrawManager.renderMap( videoDriver, player, 
                            characterManager->getGemPtr(), characterManager->getGhostsPtr(), 
                            &map, selectedTile );
    
    worldDrawManager.renderPickups( videoDriver, characterManager->getPickupsPtr() );
    worldDrawManager.renderBullets( videoDriver, characterManager->getBulletsPtr() );
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
    if ( characterManager->validateCharacterCoords( &map, newPlayerX, newPlayerY + CHARACTER_HEIGHT ) &&
         characterManager->validateCharacterCoords( &map, newPlayerX + CHARACTER_WIDTH, newPlayerY + CHARACTER_HEIGHT ) )
    {
        this->player->setPosition( newPlayerX, newPlayerY );
    }
    
    characterManager->checkPlayerPickupCollision( this->player->getX(), this->player->getY() );
}

void WorldManager::updateEnemies( )
{
    if ( createEnemies )
    {
        if ( characterManager->getGhostCount() < levelGhostCount )
        {
            characterManager->createEnemy();
        }
    }
    characterManager->moveEnemies( &map, player );
}

void WorldManager::updateBullets()
{
    characterManager->updateBullets();
}

void WorldManager::updateGem()
{
    characterManager->updateGem();
}

int WorldManager::getPlayerX()
{
    return this->player->getX();
}

int WorldManager::getPlayerY()
{
    return this->player->getY();
}

int WorldManager::getGemHealth()
{
    characterManager->getGemHealth();
}

int WorldManager::getPlayerHealth()
{
    return this->player->getHealth();
}

void WorldManager::setPlayerHealth( int value )
{
    this->player->setHealth( value );
}

bool WorldManager::fixWall()
{
    int playerIndex = worldMath.getTileIndexAtIsoPos( player->getX() + CHARACTER_WIDTH / 2, 
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


void WorldManager::setCreateMoreEnemies( bool value )
{
    this->createEnemies = value;
}

void WorldManager::calculateLevelEnemyCount( int level )
{
    this->levelGhostCount = FIRST_LEVEL_GHOST_COUNT * level;
    //randomize the ghost count a bit
    //it can take away up to 20% of total ghost count
    int randomOffset = rand() % int( ( (float)levelGhostCount / 100 ) * 20 );
    this->levelGhostCount -= randomOffset;
}

int WorldManager::getGhostCount()
{
    return characterManager->getGhostCount();
}

void WorldManager::shoot( int direction )
{
    characterManager->shoot( direction, player->getX(), player->getY() );
}

void WorldManager::clearPickups()
{
    characterManager->clearPickups();
}

void WorldManager::clearBullets()
{
    characterManager->clearBullets();
}

void WorldManager::selectTile( int mouseX, int mouseY )
{
    selectedTile = worldMath.convertIsoToIndex( mouseX - TILE_WIDTH / 2 + player->getX(), 
                                                mouseY + player->getY() );
}

bool WorldManager::buildWall()
{
    if ( selectedTile > -1 && selectedTile < map.size() )
    {
        //check if the current tile is a wall
        if ( isNeighborWall( selectedTile, 0, 0 ) )
        {
            return false;
        }
        if ( map[selectedTile].tileType == TILE_FLOOR )
        {
            bool wallPlaced = false;
            //if tile to the right is different, place a wall on east side of the tile
            if ( !validateNeighborTile( selectedTile, 1, 0, TILE_FLOOR ) )
            {
                map[selectedTile].wallPositions[WALL_POS_E] = true;
                wallPlaced = true;
            }
            //check left tile
            if ( !validateNeighborTile( selectedTile, -1, 0, TILE_FLOOR ) )
            {
                map[selectedTile].wallPositions[WALL_POS_W] = true;
                wallPlaced = true;
            }
            //check lower tile
            if ( !validateNeighborTile( selectedTile, 0, 1, TILE_FLOOR ) )
            {
                map[selectedTile].wallPositions[WALL_POS_S] = true;
                wallPlaced = true;
            }
            //check upper tile
            if ( !validateNeighborTile( selectedTile, 0, -1, TILE_FLOOR ) )
            {
                map[selectedTile].wallPositions[WALL_POS_N] = true;
                wallPlaced = true;
            }
            
            if ( wallPlaced )
            {
                map[selectedTile].wallHealth = 100;
                return true;
            }
        }
    }
    
    return false;
}