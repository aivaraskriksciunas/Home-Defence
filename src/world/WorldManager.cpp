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
    
    this->tilesXCount = mapSize;
    this->tilesYCount = mapSize;
    
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
            int index = convertPositionToIndex( posx + charIndex, posy );
            
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
                int startPosCartX = convertIndexToX( index ) * TILE_WIDTH / 2;
                int startPosCartY = convertIndexToY( index ) * TILE_HEIGHT;
                int startPosIsoX, startPosIsoY;
                convertCartToIso( this->startPosX, this->startPosY, 
                                  startPosCartX, startPosCartY );
            }
        }
        
        posy++;
        
    }
    
    ifile.close();
    orientWalls();
    
    this->player = new Player( this->startPosX, this->startPosY );
}

void WorldManager::orientWalls()
{
    for ( int y = 0; y < this->tilesYCount; y++ )
    {
        for ( int x = 0; x < this->tilesXCount; x++ )
        {
            int index = convertPositionToIndex( x, y );
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
    int neighborX = convertIndexToX( currentIndex ) + neighborDirectionX;
    int neighborY = convertIndexToY( currentIndex ) + neighborDirectionY;
    //first check if such a tile exists
    if ( neighborX < 0 || neighborX > this->tilesXCount )
    {
        return false;
    }
    
    if ( neighborY < 0 || neighborY > this->tilesYCount )
    {
        return false;
    }
    
    //now check if it has a wall
    for ( int side = 0; side < 4; side++ )
    {
        if ( map[convertPositionToIndex( neighborX, neighborY )].wallPositions[side] == true )
            return true;
    }
     
    return false;
}

bool WorldManager::validateNeighborTile( int currentIndex, int neighborDirectionX, int neighborDirectionY, int tileType )
{
    int neighborX = convertIndexToX( currentIndex ) + neighborDirectionX;
    int neighborY = convertIndexToY( currentIndex ) + neighborDirectionY;
    //first check if such a tile exists
    if ( neighborX < 0 || neighborX > this->tilesXCount )
    {
        return false;
    }
    
    if ( neighborY < 0 || neighborY > this->tilesYCount )
    {
        return false;
    }
    
    //now check if it is the correct type
    return map[convertPositionToIndex( neighborX, neighborY )].tileType == tileType;
}

void WorldManager::renderMap( Engine::VideoDriver* videoDriver )
{
    int playerPosx = this->player->getX();
    int playerPosy = this->player->getY();
    
    for ( int tileIndex = 0; tileIndex < this->map.size(); tileIndex++ )
    {
        int tileXIndex = tileIndex % this->tilesXCount;
        int tileYIndex = tileIndex / this->tilesXCount;
        
        //get the tile cartesian coordinates
        int tileCartPosX = tileXIndex * ( TILE_WIDTH / 2 );
        int tileCartPosY = tileYIndex * TILE_HEIGHT;
        
        int tileIsoX, tileIsoY;
        //convert cartesian to isometric
        convertCartToIso( tileIsoX, tileIsoY, tileCartPosX, tileCartPosY );
        
        //check if tile is visible
        if ( std::abs( playerPosx - tileIsoX ) > videoDriver->getWindowWidth() / 2 && 
             std::abs( playerPosx - ( tileIsoX + TILE_WIDTH ) ) > videoDriver->getWindowWidth() / 2 )
        {
            continue;
        }
        if ( std::abs( playerPosy - tileIsoY ) > videoDriver->getWindowHeight() / 2 &&
             std::abs( playerPosy - ( tileIsoY + TILE_HEIGHT ) ) > videoDriver->getWindowHeight() / 2 )
        {
            continue;
        }
       
        renderTile( videoDriver, tileIndex, tileIsoX, tileIsoY );
    }
    
    renderBullets( videoDriver );
}

void WorldManager::renderTile( Engine::VideoDriver* videoDriver, int tileIndex, int tileIsoX, int tileIsoY )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( map[tileIndex].texture ), 
                                  tileIsoX, tileIsoY );
    
    int wallHorTexture, wallVertTexture;
    if ( map[tileIndex].wallHealth >= 75 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_100;
        wallVertTexture = TEXTURE_WALL_VERT_100;
    }
    else if ( map[tileIndex].wallHealth < 75 && 
              map[tileIndex].wallHealth >= 50 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_75;
        wallVertTexture = TEXTURE_WALL_VERT_75;
    }
    else if ( map[tileIndex].wallHealth < 50 && 
              map[tileIndex].wallHealth >= 25 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_50;
        wallVertTexture = TEXTURE_WALL_VERT_50;
    }
    else if ( map[tileIndex].wallHealth < 25 && 
              map[tileIndex].wallHealth >= 10 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_25;
        wallVertTexture = TEXTURE_WALL_VERT_25;
    }
    else if ( map[tileIndex].wallHealth < 10 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_10;
        wallVertTexture = TEXTURE_WALL_VERT_10;
    }
    
    //draw two upper walls, if any
    if ( map[tileIndex].wallPositions[WALL_POS_N] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallHorTexture ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT );
    }
    if ( map[tileIndex].wallPositions[WALL_POS_W] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallVertTexture ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT );
    }
    
    //if there is a character on this tile, draw it too
    int playerPosx = this->player->getX();
    int playerPosy = this->player->getY();
    
    if ( isPosInsideTile( tileIndex, playerPosx, playerPosy ) || 
         isPosInsideTile( tileIndex, playerPosx, playerPosy + CHARACTER_HEIGHT ) )
    {
        this->player->draw( videoDriver );
    }
    
    //check if there is a ghost on this tile 
    for ( int ghostIndex = 0; ghostIndex < ghosts.size(); ghostIndex++ )
    {
        int ghostX = ghosts[ghostIndex]->getX();
        int ghostY = ghosts[ghostIndex]->getY();
        
        if ( isPosInsideTile( tileIndex, ghostX, ghostY ) ||
             isPosInsideTile( tileIndex, ghostX, ghostY + CHARACTER_HEIGHT ) )
        {
            this->ghosts[ghostIndex]->draw( videoDriver );
        }
    }
    
    //now draw the last lower walls.
    //these walls can go over the player texture, that's why they are drawn last
    if ( map[tileIndex].wallPositions[WALL_POS_E] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallVertTexture ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT - WALL_HEIGHT );
    }
    if ( map[tileIndex].wallPositions[WALL_POS_S] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallHorTexture ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT - WALL_HEIGHT );
    }
}

void WorldManager::renderBullets( Engine::VideoDriver* videoDriver )
{
    for ( int bulletIndex = 0; bulletIndex < bullets.size(); bulletIndex++ )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_BULLET ),
                                  bullets[bulletIndex]->getX(), 
                                  bullets[bulletIndex]->getY() );
    }
}

int WorldManager::getTileIndexAtIsoPos( int isoX, int isoY )
{
    for ( int index = 0; index < map.size(); index++ )
    {
        if ( isPosInsideTile( index, isoX, isoY ) )
        {
            return index;
        }
    }
    
    return -1;
}

bool WorldManager::isPosInsideTile( int index, int isoX, int isoY )
{
    int tileCartX = convertIndexToX( index ) * ( TILE_WIDTH / 2 );
    int tileCartY = convertIndexToY( index ) * TILE_HEIGHT;
    int tileIsoX, tileIsoY;
    convertCartToIso( tileIsoX, tileIsoY, tileCartX, tileCartY );

    if ( isoX < tileIsoX || isoX > tileIsoX + TILE_WIDTH )
        return false;
    if ( isoY < tileIsoY || isoY > tileIsoY + TILE_HEIGHT )
        return false;

    /*
     * check if the point is within the tile
     * divide the tile into 4 equal right triangles
     * now check whether or not the point is inside the triangle or not
     * 
     *     /|
     *   c/*|a
     *  ./--|
     *  / b |
     * /____|
     * 
     * . - point
     * * - sub-triangle to evaluate
     * 
     * calculate what the length of b should have been, and compare it to actual
     * length of b. If it is longer, point is outside the tile
     */

    int side_a = isoY - tileIsoY;
    if ( side_a > TILE_HEIGHT / 2 )
    {
        side_a = TILE_HEIGHT - side_a;
    }

    float side_b = std::abs( tileIsoX + ( TILE_WIDTH / 2 ) - isoX );

    float side_c = side_a / std::sin( ( M_PI / 180 ) * TILE_ANGLE_CB );

    //calculate what the actual side b should have been, if the angle cb was
    //26.5 degrees
    float actual_side_b = std::cos( ( M_PI / 180 ) * 30 ) *  side_c;

    //if the real b is shorter that what it should have been that means the point
    //is inside the triangle. Add 1 because the results are a little inaccurate 
    if ( side_b <= actual_side_b + 1 )
    {
        return true;
    }
    return false;
}

int WorldManager::getCharacterPositionOnTile( int index, int isoX, int isoY )
{
    int tileIsoX, tileIsoY;
    convertIndexToIso( tileIsoX, tileIsoY, index );
    
    if ( isoX <= tileIsoX + TILE_WIDTH / 2 &&
         isoY <= tileIsoY + TILE_HEIGHT / 2 )
    {
        return WALL_POS_W;
    }
    else if ( isoX > tileIsoX + TILE_WIDTH / 2 &&
              isoY <= tileIsoY + TILE_HEIGHT / 2 )
    {
        return WALL_POS_N;
    }
    else if ( isoX <= tileIsoX + TILE_WIDTH / 2 &&
              isoY > tileIsoY + TILE_HEIGHT / 2 )
    {
        return WALL_POS_S;
    }
    else if ( isoX > tileIsoX + TILE_WIDTH / 2 &&
              isoY > tileIsoY + TILE_HEIGHT / 2 )
    {
        return WALL_POS_E;
    }
    return WALL_POS_TOTAL;
}

bool WorldManager::isCharacterOnEdge( int tileIndex, int posx, int posy )
{
    int tileIsoX, tileIsoY;
    convertIndexToIso( tileIsoX, tileIsoY, tileIndex );
    //similar to checking which tile is the given position
    /*
     *      /|
     *    c/*|a
     *    /--|
     *   / b |
     *  /____|
     * A
     * create a sub triangle on one side based on the given position,
     * based on edge a and angle A, calculate what the b should be,
     * and compare it to actual length of b.
     * If it is the same or similar, position is on edge
     * 
     */
    
    int side_a = posy - tileIsoY;
    if ( side_a > TILE_HEIGHT / 2 )
    {
        side_a = TILE_HEIGHT - side_a;
    }

    float side_b = std::abs( tileIsoX + ( TILE_WIDTH / 2 ) - posx );
    
    //calculate the length of b based on edge a and angle A
    float calculated_side_b = side_a / std::tan( TILE_ANGLE_CB * ( M_PI / 180 ) );
    
    //compare the real and calculated length of b
    if ( side_b >= calculated_side_b - 6 && side_b <= calculated_side_b + 6 )
    {
        return true;
    }
    
    return false;
}

void WorldManager::convertCartToIso( int& isoX, int& isoY, int cartX, int cartY )
{
    isoX = cartX - cartY;
    isoY = ( cartX + cartY ) / 2;
}

void WorldManager::convertIsoToCart( int& cartX, int& cartY, int isoX, int isoY )
{
    cartX = ( 2 * isoY + isoX ) / 2;
    cartY = ( 2 * isoY - isoX ) / 2;
}

int WorldManager::convertIndexToY( int index )
{
    return index / this->tilesXCount;
}

int WorldManager::convertIndexToX( int index )
{
    return index % this->tilesXCount;
}

void WorldManager::convertIndexToIso( int& posx, int& posy, int index )
{
    int tileCartX = convertIndexToX( index ) * TILE_WIDTH / 2;
    int tileCartY = convertIndexToY( index ) * TILE_HEIGHT;
    
    convertCartToIso( posx, posy, tileCartX, tileCartY );
}

int WorldManager::convertIsoToIndex( int isoX, int isoY )
{
    int cartX, cartY;
    convertIsoToCart( cartX, cartY, isoX, isoY );
    
    int posx = cartX / TILE_WIDTH / 2;
    int posy = cartY / TILE_HEIGHT;
    
    return convertPositionToIndex( posx, posy );
}

int WorldManager::convertPositionToIndex( int posx, int posy )
{
    return ( posy * this->tilesXCount ) + posx;
}

int WorldManager::getDistanceBetweenTiles( int start, int end )
{
    int startX = convertIndexToX( start );
    int startY = convertIndexToY( start );
    
    int endX = convertIndexToX( end );
    int endY = convertIndexToY( end );
    
    //calculate distance using Pithagorean theorem
    return std::sqrt( std::pow( startX - endX, 2 ) + std::pow( startY - endY, 2 ) );
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
}

void WorldManager::moveEnemies()
{
    int playerX = player->getX();
    int playerY = player->getY();
    
    for ( int ghost = 0; ghost < ghosts.size(); ghost++ )
    {
        if ( ghosts[ghost]->getHealth() <= 0 )
        {
            ghosts.erase( ghosts.begin() + ghost );
            continue;
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
    if ( ghosts.size() < 2 )
    {
        ghosts.push_back( new Ghost( 0, 500 ) );
    }
    
    moveEnemies();
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

bool WorldManager::validateCharacterCoords( int x, int y )
{
    int currentTile = getTileIndexAtIsoPos( x , y );
    if ( currentTile == -1 )
    {
        return false;
    }
    
    //get character position on tile (N, E, S, W)
    int characterPositionOnTile = getCharacterPositionOnTile( currentTile, x, y );
    
    //check if there is a wall on the side where player is located
    if ( map[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( isCharacterOnEdge( currentTile, x, y ) )
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
    int characterPositionOnTile = getCharacterPositionOnTile( currentTile, ghostX, ghostY );
    
    //check if there is a wall on the side where player is located
    if ( map[currentTile].wallPositions[characterPositionOnTile] )
    {
        if ( isCharacterOnEdge( currentTile, ghostX, ghostY ) )
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