#pragma once
#include <cmath>
#include <vector>
#include "Character.h"
#include "../world/Tile.h"

class Ghost : public Character {
public:
    Ghost( int posx, int posy );
    void move( int changeX, int changeY, float& posx, float& posy );
    
private:
};


