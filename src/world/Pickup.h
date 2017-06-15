#pragma once

#include <cstdlib>
#include <ctime>

#include "../engine/SignalManager.h"
#include "../engine/TextureManager.h"
#include "../engine/VideoDriver.h"
#include "SFML/Graphics.hpp"

#define PICKUP_WIDTH 10
#define PICKUP_HEIGHT 10

enum PickupTypes {
    PICKUP_HEALTH,
    PICKUP_AMMO,
    PICKUP_REPAIRS,
    PICKUP_TYPES_TOTAL
};

class Pickup {
public:
    Pickup( int posx, int posy );
    
    void draw( Engine::VideoDriver* videoDriver );
    bool checkForCollision( int posx, int posy );
    
private:
    int posx, posy;
    int type;
    
    void sendPickupSignal();
    int getTextureID();
};


