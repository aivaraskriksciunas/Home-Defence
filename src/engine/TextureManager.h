#pragma once
#include <string>

#include "SignalManager.h"

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 32
#define WALL_HEIGHT 48
#define WALL_WIDTH 32

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 17

enum TextureTypes {
    TEXTURE_NONE,
    TEXTURE_TEST,
    TEXTURE_FLOOR,
    TEXTURE_GRASS,
    TEXTURE_WALL,
    TEXTURE_PLAYER,
    TEXTURE_GHOST,
    TEXTURE_BULLET,
};

enum WallTypes {
    TEXTURE_WALL_HOR_100,
    TEXTURE_WALL_HOR_75,
    TEXTURE_WALL_HOR_50,
    TEXTURE_WALL_HOR_25,
    TEXTURE_WALL_HOR_10,
    TEXTURE_WALL_VERT_100,
    TEXTURE_WALL_VERT_75,
    TEXTURE_WALL_VERT_50,
    TEXTURE_WALL_VERT_25,
    TEXTURE_WALL_VERT_10,
    TEXTURE_WALL_TOTAL
};

enum PlayerTextures {
    TEXTURE_PLAYER_SW,
    TEXTURE_PLAYER_S,
    TEXTURE_PLAYER_SE,
    TEXTURE_PLAYER_E,
    TEXTURE_PLAYER_NE,
    TEXTURE_PLAYER_N,
    TEXTURE_PLAYER_NW,
    TEXTURE_PLAYER_W,
    TEXTURE_PLAYER_TOTAL
};

namespace Engine {
class TextureManager
{
public:
    TextureManager( std::string programPath );
    static sf::Texture& getTexture( int type, int texturePart = 0 );
    
private:
    static void load( sf::Texture* texture, std::string path );
    static void loadSpriteSheet( sf::Texture texture[], int amount, std::string path, int textureHeight = TEXTURE_HEIGHT, int textureWidth = TEXTURE_WIDTH );
    
    static sf::Texture floorTexture;
    static sf::Texture testTexture;
    static sf::Texture grassTexture;
    static sf::Texture wallTextures[TEXTURE_WALL_TOTAL];
    static sf::Texture playerTexture[TEXTURE_PLAYER_TOTAL];
    static sf::Texture ghostTexture[TEXTURE_PLAYER_TOTAL];
    static sf::Texture bulletTexture;
};
}


