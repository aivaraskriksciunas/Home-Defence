#include "Defence.h"

Defence::Defence( int posx, int posy, int interval )
    : shootingInterval( interval )
{
    shootingClock.restart();
    this->posx = posx;
    this->posy = posy;
}

bool Defence::isShooting()
{
    if ( shootingClock.getElapsedTime().asMilliseconds() >= shootingInterval )
    {
        shootingClock.restart();
        return true;
    }
    return false;
}
