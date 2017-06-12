#include "Bullet.h"

Bullet::Bullet( int posx, int posy, int direction )
{
    this->posx = posx;
    this->posy = posy;
    this->direction = direction;
    this->timeSinceLaunch.restart();
}

void Bullet::move()
{
    float speedX = std::cos( direction * ( M_PI / 180 ) ) * bulletSpeed;
    float speedY = std::sin( direction * ( M_PI / 180 ) ) * bulletSpeed;
    
    posx += speedX;
    posy += speedY;
}

int Bullet::checkCollisionWithGhost( std::vector<Ghost*>* ghostList )
{
    for ( int ghostIndex = 0; ghostIndex < ghostList->size(); ghostIndex++ )
    {
        if ( posx + BULLET_SIZE / 2 >= (*ghostList)[ghostIndex]->getX() && 
             posx + BULLET_SIZE / 2 <= (*ghostList)[ghostIndex]->getX() + CHARACTER_WIDTH )
        {
            if ( posy + BULLET_SIZE / 2 >= (*ghostList)[ghostIndex]->getY() && 
                 posy + BULLET_SIZE / 2 <= (*ghostList)[ghostIndex]->getY() + CHARACTER_HEIGHT )
            {
                return ghostIndex;
            }
        }
    }
    
    return -1;
}

int Bullet::getDamage()
{
    return damage;
}

int Bullet::getX()
{
    return posx;
}

int Bullet::getY()
{
    return posy;
}

bool Bullet::isDead()
{
    if ( timeSinceLaunch.getElapsedTime().asSeconds() >= lifespan )
    {
        return true;
    }
    return false;
}