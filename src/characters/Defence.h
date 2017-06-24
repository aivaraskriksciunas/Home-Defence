#pragma once

#include "Character.h"

enum DefenceTypes {
    DEFENCE_TYPE_PLASMA_GUN,
    DEFENCE_TYPE_TOTAL
};

class Defence : public Character {
public:
    Defence( int posx, int posy, int shootingInterval );
    bool isShooting();
    
protected:
    //time in between shots
    const int shootingInterval;
    sf::Clock shootingClock;
};


