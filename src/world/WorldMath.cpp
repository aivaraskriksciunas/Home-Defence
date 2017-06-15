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
    
    int posx = cartX / TILE_WIDTH / 2;
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
    cartX = ( 2 * isoY + isoX ) / 2;
    cartY = ( 2 * isoY - isoX ) / 2;
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