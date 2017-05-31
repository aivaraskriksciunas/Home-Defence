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
            
            if ( line[charIndex] == '.' )
            {
                map[index].texture = TEXTURE_FLOOR;
                map[index].tileType = TILE_FLOOR;
            }
            else if ( line[charIndex] == '|' )
            {
                map[index].texture = TEXTURE_WALL;
                map[index].tileType = TILE_WALL;
            }
        }
        
        posy++;
        
    }
    
    ifile.close();
    orientWalls();
}

void WorldManager::orientWalls()
{
    for ( int y = 0; y < this->tilesYCount; y++ )
    {
        for ( int x = 0; x < this->tilesXCount; x++ )
        {
            int index = convertPositionToIndex( x, y );
            if ( map[index].tileType == TILE_WALL )
            {
                //check if tile is horizontal
                if ( validateNeighborTile( index, 1, 0, TILE_WALL ) &&
                     validateNeighborTile( index, -1, 0, TILE_WALL ) && 
                     validateNeighborTile( index, 0, 1, TILE_FLOOR ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_N;
                }
                else if ( validateNeighborTile( index, 1, 0, TILE_WALL ) &&
                          validateNeighborTile( index, -1, 0, TILE_WALL ) && 
                          !validateNeighborTile( index, 0, 1, TILE_FLOOR ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_S;
                }
                else if ( validateNeighborTile( index, 0, -1, TILE_GRASS ) &&
                          validateNeighborTile( index, 0, 1, TILE_FLOOR ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_N;
                }
                else if ( validateNeighborTile( index, 0, -1, TILE_FLOOR ) &&
                          validateNeighborTile( index, 0, 1, TILE_GRASS ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_S;
                }
                //check if wall is vertical
                else if ( validateNeighborTile( index, 0, -1, TILE_WALL ) &&
                          validateNeighborTile( index, 0, 1, TILE_WALL ) && 
                          validateNeighborTile( index, 1, 0, TILE_FLOOR ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_W;
                }
                else if ( validateNeighborTile( index, 0, -1, TILE_WALL ) &&
                          validateNeighborTile( index, 0, 1, TILE_WALL ) && 
                          !validateNeighborTile( index, 1, 0, TILE_FLOOR )  )
                {
                    map[index].tileSubType = TEXTURE_WALL_E;
                }
                else if ( validateNeighborTile( index, 1, 0, TILE_FLOOR ) &&
                          validateNeighborTile( index, -1, 0, TILE_GRASS ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_W;
                }
                else if ( validateNeighborTile( index, 1, 0, TILE_GRASS ) &&
                          validateNeighborTile( index, -1, 0, TILE_FLOOR ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_E;
                }
                
                //check for corners
                if ( validateNeighborTile( index, 0, 1, TILE_WALL ) &&
                     validateNeighborTile( index, 1, 0, TILE_WALL ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_NW;
                }
                else if ( validateNeighborTile( index, 0, 1, TILE_WALL ) &&
                          validateNeighborTile( index, -1, 0, TILE_WALL ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_NE;
                }
                else if ( validateNeighborTile( index, 0, -1, TILE_WALL ) &&
                          validateNeighborTile( index, 1, 0, TILE_WALL ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_SW;
                }
                else if ( validateNeighborTile( index, 0, -1, TILE_WALL ) &&
                          validateNeighborTile( index, -1, 0, TILE_WALL ) )
                {
                    map[index].tileSubType = TEXTURE_WALL_SE;
                }
                
            }
            
        }
    }
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
    if ( map[convertPositionToIndex( neighborX, neighborY )].tileType == tileType )
        return true;
    else 
        return false;
}

void WorldManager::renderMap( Engine::VideoDriver* videoDriver )
{
    for ( int tileIndex = 0; tileIndex < this->map.size(); tileIndex++ )
    {
        int tileXIndex = tileIndex % this->tilesXCount;
        int tileYIndex = tileIndex / this->tilesXCount;
        
        //get the tiles cartesian coordinates
        int tileCartPosX = tileXIndex * ( TILE_WIDTH / 2 );
        int tileCartPosY = tileYIndex * TILE_HEIGHT;
        
        int tileIsoX, tileIsoY;
        //convert cartesian to isometric
        convertCartToIso( tileIsoX, tileIsoY, tileCartPosX, tileCartPosY );
        
        if ( map[tileIndex].tileType == TILE_WALL )
        {
            videoDriver->drawTexture( Engine::TextureManager::getTexture( map[tileIndex].texture, map[tileIndex].tileSubType ), 
                                      tileIsoX + this->offsetX, tileIsoY + this->offsetY - WALL_HEIGHT );
        }
        else 
        {
            videoDriver->drawTexture( Engine::TextureManager::getTexture( map[tileIndex].texture ), 
                                      tileIsoX + this->offsetX, tileIsoY + this->offsetY );
        }
    }
}

void WorldManager::scrollMap( int scrollX, int scrollY ) 
{
    this->offsetX += scrollX;
    this->offsetY += scrollY;
}

void WorldManager::convertCartToIso( int& isoX, int& isoY, int cartX, int cartY )
{
    isoX = ( cartX - cartY );
    isoY = ( cartX + cartY ) / 2;
}

int WorldManager::convertIndexToY( int index )
{
    return index / this->tilesXCount;
}

int WorldManager::convertIndexToX( int index )
{
    return index % this->tilesXCount;
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