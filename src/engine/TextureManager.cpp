#include <SFML/Graphics/Texture.hpp>

#include "TextureManager.h"
#include "iostream"

using namespace Engine;

sf::Texture TextureManager::floorTexture;
sf::Texture TextureManager::testTexture;
sf::Texture TextureManager::grassTexture;
sf::Texture TextureManager::wallTextures[TEXTURE_WALL_TOTAL];
sf::Texture TextureManager::playerTexture[TEXTURE_PLAYER_TOTAL];

TextureManager::TextureManager( std::string programPath )
{
    load( &this->floorTexture, programPath + "/media/tiles/floor.png" );
    load( &this->testTexture, programPath + "/media/tiles/test.png" );
    load( &this->grassTexture, programPath + "/media/tiles/grass.png" );
    loadSpriteSheet( this->wallTextures, TEXTURE_WALL_TOTAL, programPath + "/media/tiles/wall.png", WALL_HEIGHT, WALL_WIDTH );
    loadSpriteSheet( this->playerTexture, TEXTURE_PLAYER_TOTAL, programPath + "/media/characters/player.png", CHARACTER_HEIGHT, CHARACTER_WIDTH );
}

void TextureManager::load( sf::Texture* texture, std::string path )
{
    if ( !texture->loadFromFile( path ) )
    {
        SignalManager::sendSignal( SIG_TEXTURE_LOAD_ERROR );
    }
}

void TextureManager::loadSpriteSheet( sf::Texture texture[], int amount, std::string path, int textureHeight, int textureWidth )
{
    for ( int textIndex = 0; textIndex < amount; textIndex++ )
    {
        if ( !texture[textIndex].loadFromFile( path, sf::IntRect( textureWidth * textIndex, 0, textureWidth, textureHeight ) ) )
        {
            SignalManager::sendSignal( SIG_TEXTURE_LOAD_ERROR );
        }
    }
}

sf::Texture& TextureManager::getTexture( int type, int texturePart )
{
    switch ( type )
    {
        case TEXTURE_FLOOR:
            return floorTexture;
            break;
        case TEXTURE_WALL:
            return wallTextures[texturePart];
            break;
        case TEXTURE_GRASS:
            return grassTexture;
            break;
        case TEXTURE_TEST:
            return testTexture;
            break;
        case TEXTURE_PLAYER:
            return playerTexture[texturePart];
            break;
    }
    return testTexture;
}
