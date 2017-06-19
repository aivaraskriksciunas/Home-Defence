#include "Gem.h"

Gem::Gem( int posx, int posy )
{
    this->posx = posx;
    this->posy = posy;
    this->health = MAX_GEM_HEALTH;
}

void Gem::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( TEXTURE_GEM ),
                              posx, posy );
}

void Gem::takeDamage( int damage )
{
    this->health -= damage;
}

int Gem::getHealth()
{
    return this->health;
}

bool Gem::hasCollided( int posx, int posy )
{
    if ( posx >= this->posx && posx <= this->posx + GEM_SIZE )
    {
        if ( posy >= this->posy && posy <= this->posy + GEM_SIZE )
        {
            return true;
        }
    }
    
    return false;
}

int Gem::getX()
{
    return this->posx;
}

int Gem::getY()
{
    return this->posy;
}