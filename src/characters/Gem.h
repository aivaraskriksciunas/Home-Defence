#pragma once
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"

#define GEM_SIZE 20
#define MAX_GEM_HEALTH 100

class Gem {
public:
    Gem( int posx, int posy );
    void draw( Engine::VideoDriver* videoDriver );
    
    void takeDamage( int damage );
    int getHealth();
    
    bool hasCollided( int posx, int posy );
    
    int getX();
    int getY();
    
private:
    int posx, posy;
    int health;
    
    
};

