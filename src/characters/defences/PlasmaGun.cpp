#include "PlasmaGun.h"

PlasmaGun::PlasmaGun( int posx, int posy )
    : Defence( posx, posy, SHOOTING_INTERVAL )
{
    this->textureIndex = TEXTURE_DEFENCE_PLASMA_GUN;
}

