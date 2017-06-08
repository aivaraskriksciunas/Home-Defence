#include "Character.h"

void Character::setDirection( int direction )
{
    this->direction = direction;
}

void Character::move( int& newPosx, int& newPosy )
{
    newPosx = this->posx;
    newPosy = this->posy;
    switch ( this->direction )
    {
        case TEXTURE_PLAYER_SW:
            newPosy += this->speed;
            newPosx -= this->speed;
            break;
        case TEXTURE_PLAYER_S:
            newPosy += this->speed;
            break;
        case TEXTURE_PLAYER_SE:
            newPosx += this->speed;
            newPosy += this->speed;
            break;
        case TEXTURE_PLAYER_E:
            newPosx += this->speed;
            break;
        case TEXTURE_PLAYER_NE:
            newPosy -= this->speed;
            newPosx += this->speed;
            break;
        case TEXTURE_PLAYER_N:
            newPosy -= this->speed;
            break;
        case TEXTURE_PLAYER_NW:
            newPosy -= this->speed;
            newPosx -= this->speed;
            break;
        case TEXTURE_PLAYER_W:
            newPosx -= this->speed;
            break;
    }
        
}

void Character::setPosition( int posx, int posy )
{
    this->posx = posx;
    this->posy = posy;
}

void Character::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( textureIndex, direction ), 
                                      this->posx, this->posy );
}

int Character::getX()
{
    return this->posx;
}

int Character::getY()
{
    return this->posy;
}
