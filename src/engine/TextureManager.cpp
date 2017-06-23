#include <SFML/Graphics/Texture.hpp>

#include "TextureManager.h"
#include "iostream"

using namespace Engine;

sf::Texture TextureManager::floorTexture;
sf::Texture TextureManager::grassTexture;
sf::Texture TextureManager::emptyTileTexture;
sf::Texture TextureManager::bulletTexture;
sf::Texture TextureManager::wallTextures[TEXTURE_WALL_TOTAL];
sf::Texture TextureManager::playerTexture[TEXTURE_PLAYER_TOTAL];
sf::Texture TextureManager::ghostTexture[TEXTURE_PLAYER_TOTAL];
sf::Texture TextureManager::gemTexture;
sf::Texture TextureManager::bulletIcon;
sf::Texture TextureManager::heartIcon;
sf::Texture TextureManager::hammerIcon;
sf::Texture TextureManager::gemIcon;
sf::Font TextureManager::basicFont;

TextureManager::TextureManager( std::string programPath )
{
    load( &this->floorTexture, programPath + "/media/tiles/floor.png" );
    load( &this->grassTexture, programPath + "/media/tiles/grass.png" );
    load( &this->emptyTileTexture, programPath + "/media/tiles/empty.png" );
    load( &this->bulletTexture, programPath + "/media/characters/bullet.png" );
    load( &this->gemTexture, programPath + "/media/characters/gem.png" );
    load( &this->bulletIcon, programPath + "/media/icons/bullet.png" );
    load( &this->heartIcon, programPath + "/media/icons/heart.png" );
    load( &this->hammerIcon, programPath + "/media/icons/hammer.png" );
    load( &this->gemIcon, programPath + "/media/icons/gem.png" );
    loadSpriteSheet( this->wallTextures, TEXTURE_WALL_TOTAL, programPath + "/media/tiles/wall.png", WALL_HEIGHT, WALL_WIDTH );
    loadSpriteSheet( this->playerTexture, TEXTURE_PLAYER_TOTAL, programPath + "/media/characters/player.png", CHARACTER_HEIGHT, CHARACTER_WIDTH );
    loadSpriteSheet( this->ghostTexture, TEXTURE_PLAYER_TOTAL, programPath + "/media/characters/ghost.png", CHARACTER_HEIGHT, CHARACTER_WIDTH );
    
    loadFont( &this->basicFont, programPath + "/media/fonts/PTM55FT.ttf" );
}

void TextureManager::load( sf::Texture* texture, std::string path )
{
    if ( !texture->loadFromFile( path ) )
    {
        SignalManager::sendSignal( SIG_TEXTURE_LOAD_ERROR );
    }
}

void TextureManager::loadFont( sf::Font* font, std::string path )
{
    if ( !font->loadFromFile( path ) )
    {
        SignalManager::sendSignal( SIG_RESOURCE_LOAD_ERROR );
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
        case TEXTURE_PLAYER:
            return playerTexture[texturePart];
            break;
        case TEXTURE_GHOST:
            return ghostTexture[texturePart];
            break;
        case TEXTURE_BULLET:
            return bulletTexture;
            break;
        case TEXTURE_ICON_BULLET:
            return bulletIcon;
            break;
        case TEXTURE_ICON_HEART:
            return heartIcon;
            break;
        case TEXTURE_ICON_HAMMER:
            return hammerIcon;
            break;
        case TEXTURE_ICON_GEM:
            return gemIcon;
            break;
        case TEXTURE_GEM:
            return gemTexture;
            break;
    }
    return emptyTileTexture;
}

sf::Font& TextureManager::getFont( int type )
{
    switch ( type )
    {
        case FONT_SIMPLE:
            return basicFont;
            break;
    }
}
