#pragma once
#include "SFML/Graphics.hpp"

namespace World {
enum TileTypes {
    TILE_NONE,
    TILE_TEST,
    TILE_FLOOR,
    TILE_WALL,
    TILE_GRASS,
    TILE_DOOR
};

enum WallTypes {
    TILE_WALL_HOR,
    TILE_WALL_VERT,
    TILE_WALL_TOTAL
};

struct Tile {
    int tileType;
    int texture;
    int tileSubType; //used for tiles that might have different orientation (e.g. walls)
};
}

