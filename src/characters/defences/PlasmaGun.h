#pragma once
#include "../Defence.h"

class PlasmaGun : public Defence {
public:
    PlasmaGun( int posx, int posy );
    
private:
    const int SHOOTING_INTERVAL = 1500;
};


