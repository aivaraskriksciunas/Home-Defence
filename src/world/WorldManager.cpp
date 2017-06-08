#include "WorldManager.h"

using namespace World;

void WorldManager::GenerateMap( std::string path )
{
    std::ifstream ifile( path );
    
    if ( !ifile.is_open() )
    {
        Engine::SignalManager::sendSignal( SIG_MAP_LOAD_ERROR );
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
}

void WorldManager::renderTile( Engine::VideoDriver* videoDriver, int tileIndex, int tileIsoX, int tileIsoY )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( map[tileIndex].texture ), 
                                  tileIsoX + this->offsetX, tileIsoY + this->offsetY );
    
    //draw two upper walls, if any
    if ( map[tileIndex].wallPositions[WALL_POS_N] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, TEXTURE_WALL_HOR ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT );
    }
    if ( map[tileIndex].wallPositions[WALL_POS_W] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, TEXTURE_WALL_VERT ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT );
    }
    
    //if there is a character on this tile, draw it too
    int playerPosx = this->player->getX();
    int playerPosy = this->player->getY();
    
    if ( playerPosx >= tileIsoX && playerPosx < tileIsoX + TILE_WIDTH )
    {
        if ( ( playerPosy >= tileIsoY && playerPosy < tileIsoY + TILE_HEIGHT ) ||
             ( playerPosy + CHARACTER_HEIGHT >= tileIsoY && playerPosy + CHARACTER_HEIGHT < tileIsoY + TILE_HEIGHT ) )
        {
            this->player->draw( videoDriver );
        }
    }
    
    //now draw the last lower walls.
    //these walls can go over the player texture, that's why they are drawn last
    if ( map[tileIndex].wallPositions[WALL_POS_E] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, TEXTURE_WALL_VERT ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT - WALL_HEIGHT );
    }
    if ( map[tileIndex].wallPositions[WALL_POS_S] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, TEXTURE_WALL_HOR ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT - WALL_HEIGHT );
    }
}

void WorldManager::scrollMap( int scrollX, int scrollY ) 
{
    this->offsetX += scrollX;
    this->offsetY += scrollY;
}

int WorldManager::getTileIndexAtIsoPos( int isoX, int isoY )
{
    for ( int index = 0; index < map.size(); index++ )
    {
        int tileCartX = convertIndexToX( index ) * ( TILE_WIDTH / 2 );
        int tileCartY = convertIndexToY( index ) * TILE_HEIGHT;
        int tileIsoX, tileIsoY;
        convertCartToIso( tileIsoX, tileIsoY, tileCartX, tileCartY );
        
        if ( isoX < tileIsoX || isoX > tileIsoX + TILE_WIDTH )
            continue;
        if ( isoY < tileIsoY || isoY > tileIsoY + TILE_HEIGHT )
            continue;
        
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
            return index;
        }
    }
    
    return -1;
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
    float calculated_side_b = std::tan( TILE_ANGLE_CB * ( M_PI / 180 ) ) * side_a;
    
    //compare the real and calculated length of b
    if ( side_b >= calculated_side_b - 1 && side_b <= calculated_side_b + 1 )
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
    if ( validateCharacterCoords( newPlayerX, newPlayerY ) )
    {
        this->player->setPosition( newPlayerX, newPlayerY );
    }
}

int WorldManager::getPlayerX()
{
    return this->player->getX();
}

int WorldManager::getPlayerY()
{
    return this->player->getY();
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