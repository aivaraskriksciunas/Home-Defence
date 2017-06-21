#include "Ghost.h"

Ghost::Ghost( int posx, int posy )
{
    this->posx = posx;
    this->posy = posy;
    this->speed = 1.5;
    this->textureIndex = TEXTURE_GHOST;
}

void Ghost::move( int changeX, int changeY, float& posx, float& posy )
{
    posx = this->posx;
    posy = this->posy;
    
    if ( changeX < 0 && changeY < 0 )
    {
        this->direction = TEXTURE_PLAYER_NW;
        posx -= speed / 2;
        posy -= speed / 2;
    }
    else if ( changeX > 0 && changeY < 0 )
    {
        this->direction = TEXTURE_PLAYER_NE;
        posx += speed / 2;
        posy -= speed / 2;
    }
    else if ( changeX < 0 && changeY > 0 )
    {
        this->direction = TEXTURE_PLAYER_SW;
        posx -= speed / 2;
        posy += speed / 2;
    }
    else if ( changeX > 0 && changeY > 0 )
    {
        this->direction = TEXTURE_PLAYER_SE;
        posx += speed / 2;
        posy += speed / 2;
    }
    else if ( changeX > 0 )
    {
        this->direction = TEXTURE_PLAYER_E;
        posx += speed;
    }
    else if ( changeX < 0 )
    {
        this->direction = TEXTURE_PLAYER_W;
        posx -= speed;
    }
    else if ( changeY > 0 )
    {
        this->direction = TEXTURE_PLAYER_S;
        posy += speed;
    }
    else if ( changeY < 0 )
    {
        this->direction = TEXTURE_PLAYER_N;
        posy -= speed;
    }
}