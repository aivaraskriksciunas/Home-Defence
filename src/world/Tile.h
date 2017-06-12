#pragma once

#define TILE_ANGLE_CB 26.565

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
    int tileSubType; //used for tiles that might have different orientation (e.g. walls)
    int wallHealth = 100;
    bool wallPositions[4] = { false, false, false, false }; //which sides the walls are located at
};
}

