#include "WorldRenderManager.h"

using namespace World;

void WorldRenderManager::renderMap( Engine::VideoDriver* videoDriver, 
                                    Player* player, Gem* gem,
                                    std::vector<Ghost*>* ghosts,
                                    std::vector<Tile>* map,
                                    int selectedTile )
{
    int playerPosx = player->getX();
    int playerPosy = player->getY();
    
    for ( int tileIndex = 0; tileIndex < map->size(); tileIndex++ )
    {
        int tileXIndex = worldMath.convertIndexToX( tileIndex );
        int tileYIndex = worldMath.convertIndexToY( tileIndex );
        
        //get the tile cartesian coordinates
        int tileCartPosX = tileXIndex * ( TILE_WIDTH / 2 );
        int tileCartPosY = tileYIndex * TILE_HEIGHT;
        
        int tileIsoX, tileIsoY;
        //convert cartesian to isometric
        worldMath.convertCartToIso( tileIsoX, tileIsoY, tileCartPosX, tileCartPosY );
        
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
        
        if ( tileIndex == selectedTile )
            renderTile( videoDriver, map, player, gem, ghosts, tileIndex, tileIsoX, tileIsoY, true );
        else
            renderTile( videoDriver, map, player, gem, ghosts, tileIndex, tileIsoX, tileIsoY, false );
    }
    
}

void WorldRenderManager::renderPickups( Engine::VideoDriver* videoDriver, std::vector<Pickup*>* pickups )
{
    for ( int pickupIndex = 0; pickupIndex < pickups->size(); pickupIndex++ )
    {
        (*pickups)[pickupIndex]->draw( videoDriver );
    }
}

void WorldRenderManager::renderBullets( Engine::VideoDriver* videoDriver, std::vector<Bullet*>* bullets )
{
    for ( int bulletIndex = 0; bulletIndex < bullets->size(); bulletIndex++ )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_BULLET ),
                                  (*bullets)[bulletIndex]->getX(), 
                                  (*bullets)[bulletIndex]->getY() );
    }
}

void WorldRenderManager::renderTile( Engine::VideoDriver* videoDriver,
                                     std::vector<Tile>* map,
                                     Player* player, Gem* gem,
                                     std::vector<Ghost*>* ghosts, 
                                     int tileIndex, 
                                     int tileIsoX, int tileIsoY,
                                     bool tileSelected )
{
    sf::Color textureColor = sf::Color::White;
    if ( tileSelected )
    {
        textureColor = selectedTileColor;
    }
    videoDriver->drawTexture( Engine::TextureManager::getTexture( (*map)[tileIndex].texture ), 
                                      tileIsoX, tileIsoY, textureColor );
    
    int wallHorTexture, wallVertTexture;
    if ( (*map)[tileIndex].wallHealth >= 75 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_100;
        wallVertTexture = TEXTURE_WALL_VERT_100;
    }
    else if ( (*map)[tileIndex].wallHealth < 75 && 
              (*map)[tileIndex].wallHealth >= 50 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_75;
        wallVertTexture = TEXTURE_WALL_VERT_75;
    }
    else if ( (*map)[tileIndex].wallHealth < 50 && 
              (*map)[tileIndex].wallHealth >= 25 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_50;
        wallVertTexture = TEXTURE_WALL_VERT_50;
    }
    else if ( (*map)[tileIndex].wallHealth < 25 && 
              (*map)[tileIndex].wallHealth >= 10 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_25;
        wallVertTexture = TEXTURE_WALL_VERT_25;
    }
    else if ( (*map)[tileIndex].wallHealth < 10 )
    {
        wallHorTexture = TEXTURE_WALL_HOR_10;
        wallVertTexture = TEXTURE_WALL_VERT_10;
    }
    
    //draw two upper walls, if any
    if ( (*map)[tileIndex].wallPositions[WALL_POS_N] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallHorTexture ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT, textureColor );
    }
    if ( (*map)[tileIndex].wallPositions[WALL_POS_W] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallVertTexture ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT / 2 - WALL_HEIGHT, textureColor );
    }
    
    //if there is a character on this tile, draw it too
    int playerPosx = player->getX();
    int playerPosy = player->getY();
    
    if ( worldMath.isPosInsideTile( tileIndex, playerPosx, playerPosy ) || 
         worldMath.isPosInsideTile( tileIndex, playerPosx, playerPosy + CHARACTER_HEIGHT ) )
    {
        player->draw( videoDriver );
    }
    //check if there's a gem on this tile
    if ( worldMath.isPosInsideTile( tileIndex, gem->getX(), gem->getY() ) ||
         worldMath.isPosInsideTile( tileIndex, gem->getX(), gem->getY() + GEM_SIZE ) )
    {
        gem->draw( videoDriver );
    }
    
    //check if there is a ghost on this tile 
    for ( int ghostIndex = 0; ghostIndex < (*ghosts).size(); ghostIndex++ )
    {
        int ghostX = (*ghosts)[ghostIndex]->getX();
        int ghostY = (*ghosts)[ghostIndex]->getY();
        
        if ( worldMath.isPosInsideTile( tileIndex, ghostX, ghostY ) ||
             worldMath.isPosInsideTile( tileIndex, ghostX, ghostY + CHARACTER_HEIGHT ) )
        {
            (*ghosts)[ghostIndex]->draw( videoDriver );
        }
    }
    
    //now draw the last lower walls.
    //these walls can go over the player texture, that's why they are drawn last
    if ( (*map)[tileIndex].wallPositions[WALL_POS_E] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallVertTexture ),
                                  tileIsoX + TILE_WIDTH / 2, tileIsoY + TILE_HEIGHT - WALL_HEIGHT, textureColor );
    }
    if ( (*map)[tileIndex].wallPositions[WALL_POS_S] )
    {
        videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_WALL, wallHorTexture ),
                                 tileIsoX, tileIsoY + TILE_HEIGHT - WALL_HEIGHT, textureColor );
    }
}