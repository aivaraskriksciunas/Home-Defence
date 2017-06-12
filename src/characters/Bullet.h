#include <cmath>
#include "Ghost.h"

#define BULLET_SIZE 8

class Bullet {
public:
    Bullet( int posx, int posy, int direction );
    void move();
    
    int checkCollisionWithGhost( std::vector<Ghost*>* ghostList );
    int getDamage();
    
    int getX();
    int getY();
    
    bool isDead();
    
private:
    float posx, posy;
    int direction;
    
    const int bulletSpeed = 4;
    const int damage = 25;
    //bullet lifespan in seconds since launch
    const int lifespan = 3;
    
    //each bullet can last a certain amount of time only.
    //this timer is to check how much time has passed
    sf::Clock timeSinceLaunch;
};


