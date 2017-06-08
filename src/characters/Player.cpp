#include "Player.h"

Player::Player( int posx, int posy )
{
    this->posx = posx;
    this->posy = posy;
    this->textureIndex = TEXTURE_PLAYER;
    this->direction = TEXTURE_PLAYER_S;
    this->speed = 1;
}




