#include "WorldMath.h"

using namespace World;

int WorldMath::tilesXCount;
int WorldMath::tilesYCount;

void WorldMath::setWorldSize( int tilesXCount, int tilesYCount )
{
    this->tilesXCount = tilesXCount;
    this->tilesYCount = tilesYCount;
}

int WorldMath::convertIndexToY( int index )
{
    return index / this->tilesXCount;
}

int WorldMath::convertIndexToX( int index )
{
    return index % this->tilesXCount;
}

void WorldMath::convertIndexToIso( int& posx, int& posy, int index )
{
    int tileCartX = convertIndexToX( index ) * TILE_WIDTH / 2;
    int tileCartY = convertIndexToY( index ) * TILE_HEIGHT;
    
    convertCartToIso( posx, posy, tileCartX, tileCartY );
}

int WorldMath::convertIsoToIndex( int isoX, int isoY )
{
    int cartX, cartY;
    convertIsoToCart( cartX, cartY, isoX, isoY );
    
    int posx = cartX / ( TILE_WIDTH / 2 );
    int posy = cartY / TILE_HEIGHT;
    
    return convertPositionToIndex( posx, posy );
}

int WorldMath::convertPositionToIndex( int posx, int posy )
{
    return ( posy * this->tilesXCount ) + posx;
}

int WorldMath::getDistanceBetweenTiles( int start, int end )
{
    int startX = convertIndexToX( start );
    int startY = convertIndexToY( start );
    
    int endX = convertIndexToX( end );
    int endY = convertIndexToY( end );
    
    //calculate distance using Pithagorean theorem
    return std::sqrt( std::pow( startX - endX, 2 ) + std::pow( startY - endY, 2 ) );
}

void WorldMath::convertCartToIso( int& isoX, int& isoY, int cartX, int cartY )
{
    isoX = cartX - cartY;
    isoY = ( cartX + cartY ) / 2;
}

void WorldMath::convertIsoToCart( int& cartX, int& cartY, int isoX, int isoY )
{
    cartX = ( ( 2 * isoY ) + isoX ) / 2;
    cartY = ( ( 2 * isoY ) - isoX ) / 2;
}

int WorldMath::getTilesXCount() 
{
    return this->tilesXCount;
}

int WorldMath::getTilesYCount()
{
    return this->tilesYCount;
}

bool WorldMath::isCharacterOnEdge( int tileIndex, int posx, int posy )
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

bool WorldMath::isPosInsideTile( int index, int isoX, int isoY )
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


int WorldMath::getCharacterPositionOnTile( int index, int isoX, int isoY )
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

void WorldMath::getClosestTargetPos( int posx, int posy, int& targetPosX, int& targetPosY,
                                     Player* player, Gem* gem )
{
    //calculate direct distance to each target
    int distToPlayer = std::sqrt( std::pow( posx - player->getX(), 2 ) + 
                                  std::pow( posy - player->getY(), 2 ) );
    
    int distToGem = std::sqrt( std::pow( posx - gem->getX(), 2 ) + 
                               std::pow( posy - gem->getY(), 2 ) );
    
    //check which target is closer and return it's position
    if ( distToGem < distToPlayer )
    {
        targetPosX = gem->getX();
        targetPosY = gem->getY();
    }
    else 
    {
        targetPosX = player->getX();
        targetPosY = player->getY();
    }
}

int WorldMath::getTileIndexAtIsoPos( int isoX, int isoY )
{
    //we imagine the map is divided in to TILE_WIDTH by TILE_HEIGHT squares
    //calculate the position of our current square
    
    //we first get the square index, then we find it's coordinates
    //make sure to cast index to an int, otherwise we'll just get the same result
    int squareX = 0;
    int squareY = int( isoY / TILE_HEIGHT ) * TILE_HEIGHT;
    
    //if position is on the negative (left) side, offset it by one tile,
    //otherwise we would get middle squares with same x positions
    if ( isoX < 0 )
        squareX = int( ( isoX - TILE_WIDTH ) / TILE_WIDTH ) * TILE_WIDTH; 
    else
        squareX = int( isoX / TILE_WIDTH ) * TILE_WIDTH; 
    
    //the square's position is also equal to position of a tile
    //since we have some tiles position, we can calculate it's index
    //find the tile cartesian coordinates
    int tileCartX, tileCartY;
    convertIsoToCart( tileCartX, tileCartY, squareX, squareY );
    //now get tile X and Y indexes
    int tileIndexX = tileCartX / ( TILE_WIDTH / 2 );
    int tileIndexY = tileCartY / TILE_HEIGHT;
    //now just get the index
    int detectedTileIndex = convertPositionToIndex( tileIndexX, tileIndexY );
    
    //test the current tile
    if ( isPosInsideTile( detectedTileIndex, isoX, isoY ) )
    {
        return detectedTileIndex;
    }
    
    //test the neighbor tiles, because they take up part of a square as well
    //west tile
    if ( convertIndexToX( detectedTileIndex ) > 0 )
    {
        if ( isPosInsideTile( detectedTileIndex - 1, isoX, isoY ) )
            return detectedTileIndex - 1;
    }
    //east tile
    if ( convertIndexToX( detectedTileIndex ) < getTilesXCount() )
    {
        if ( isPosInsideTile( detectedTileIndex + 1, isoX, isoY ) )
            return detectedTileIndex + 1;
    }
    //north tile
    if ( convertIndexToY( detectedTileIndex ) > 0 )
    {
        if ( isPosInsideTile( detectedTileIndex - getTilesXCount(), isoX, isoY ) )
            return detectedTileIndex - getTilesXCount();
    }
    //south tile
    if ( convertIndexToX( detectedTileIndex ) < getTilesYCount() )
    {
        if ( isPosInsideTile( detectedTileIndex + getTilesYCount(), isoX, isoY ) )
            return detectedTileIndex + getTilesYCount();
    }
    
    return -1;
}