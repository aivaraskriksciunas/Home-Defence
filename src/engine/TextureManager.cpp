#include <SFML/Graphics/Texture.hpp>

#include "TextureManager.h"
#include "iostream"

using namespace Engine;

sf::Texture TextureManager::floorTexture;
sf::Texture TextureManager::testTexture;
sf::Texture TextureManager::grassTexture;
sf::Texture TextureManager::wallTextures[TEXTURE_WALL_TOTAL];

TextureManager::TextureManager( std::string programPath )
{
    load( &this->floorTexture, programPath + "/media/tiles/floor.png" );
    load( &this->testTexture, programPath + "/media/tiles/test.png" );
    load( &this->grassTexture, programPath + "/media/tiles/grass.png" );
    loadSpriteSheet( this->wallTextures, TEXTURE_WALL_TOTAL, programPath + "/media/tiles/wall.png", TEXTURE_HEIGHT + WALL_HEIGHT );
}

void TextureManager::load( sf::Texture* texture, std::string path )
{
    if ( !texture->loadFromFile( path ) )
    {
        SignalManager::sendSignal( SIG_TEXTURE_LOAD_ERROR );
    }
}

void TextureManager::loadSpriteSheet( sf::Texture texture[], int amount, std::string path, int textureHeight )
{
    for ( int textIndex = 0; textIndex < amount; textIndex++ )
    {
        if ( !texture[textIndex].loadFromFile( path, sf::IntRect( TEXTURE_WIDTH * textIndex, 0, TEXTURE_WIDTH, textureHeight ) ) )
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
    }
    return testTexture;
}
