#include "Pickup.h"

Pickup::Pickup( int posx, int posy )
{
    srand( time( 0 ) );
    this->posx = posx;
    this->posy = posy;
    
    this->type = rand() % PICKUP_TYPES_TOTAL;
}

void Pickup::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( getTextureID() ),
                              this->posx, this->posy );
}

bool Pickup::checkForCollision( int x, int y )
{
    if ( x >= this->posx && x <= this->posx + PICKUP_WIDTH )
    {
        if ( y >= this->posy && y <= this->posy + PICKUP_HEIGHT )
        {
            sendPickupSignal();
            return true;
        }
    }
    return false;
}

void Pickup::sendPickupSignal()
{
    switch ( this->type )
    {
        case PICKUP_AMMO:
            Engine::SignalManager::sendSignal( SIG_PICKUP_AMMO );
            break;
        case PICKUP_HEALTH:
            Engine::SignalManager::sendSignal( SIG_PICKUP_HEALTH );
            break;  
        case PICKUP_REPAIRS:
            Engine::SignalManager::sendSignal( SIG_PICKUP_REPAIRS );
            break;
    }
}

void Pickup::getTextureID()
{
    switch ( this->type )
    {
        case PICKUP_AMMO:
            return TEXTURE_ICON_BULLET;
            break;
        case PICKUP_HEALTH:
            return TEXTURE_ICON_HEART;
            break;  
        case PICKUP_REPAIRS:
            return TEXTURE_ICON_HAMMER;
            break;
    }
}