#pragma once
#include <string>

#include "SignalManager.h"

#define TEXTURE_WIDTH 41
#define TEXTURE_HEIGHT 25
#define WALL_HEIGHT 20

enum TextureTypes {
    TEXTURE_NONE,
    TEXTURE_TEST,
    TEXTURE_FLOOR,
    TEXTURE_GRASS,
    TEXTURE_WALL
};

enum WallTypes {
    TEXTURE_WALL_N,
    TEXTURE_WALL_E,
    TEXTURE_WALL_S,
    TEXTURE_WALL_W,
    TEXTURE_WALL_NW,
    TEXTURE_WALL_SW,
    TEXTURE_WALL_SE,
    TEXTURE_WALL_NE,
    TEXTURE_WALL_TOTAL
};

namespace Engine {
class TextureManager
{
public:
    TextureManager( std::string programPath );
    static sf::Texture& getTexture( int type, int texturePart = 0 );
    
private:
    static void load( sf::Texture* texture, std::string path );
    static void loadSpriteSheet( sf::Texture texture[], int amount, std::string path, int textureHeight = TEXTURE_HEIGHT );
    
    static sf::Texture floorTexture;
    static sf::Texture testTexture;
    static sf::Texture grassTexture;
    static sf::Texture wallTextures[TEXTURE_WALL_TOTAL];
};
}


