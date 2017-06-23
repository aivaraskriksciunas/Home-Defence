#pragma once

//for TEXTURE_WIDTH and TEXTURE_HEIGHT macros
//yes, I know it's terrible
#include "../engine/TextureManager.h"

#define TILE_ANGLE_CB 26.565

#define TILE_WIDTH TEXTURE_WIDTH
#define TILE_HEIGHT TEXTURE_HEIGHT

namespace World {
enum TileTypes {
    TILE_NONE,
    TILE_TEST,
    TILE_FLOOR,
    TILE_GRASS,
    TILE_DOOR
};

enum WallPositionNames {
    WALL_POS_N,
    WALL_POS_E,
    WALL_POS_S,
    WALL_POS_W,
    WALL_POS_TOTAL
};

enum WallTypes 
{
    WALL_TYPE_WOOD,
    WALL_TYPE_BRICK,
    WALL_TYPE_TOTAL
};

/* wall positions:
 * 
 *   w/\n
 *   /  \
 *   \  /
 *   s\/e
 */

struct Tile {
    int tileType;
    int texture;
    int wallType; //keeps the type of wall on the current tile
    int wallHealth;
    int wallMaxHealth;
    bool wallPositions[4] = { false, false, false, false }; //which sides the walls are located at
};
}

