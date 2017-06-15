#pragma once
#include "SFML/Graphics.hpp"
#include "../engine/TextureManager.h"
#include "../engine/VideoDriver.h"
#include "../world/Tile.h"

class Character {
public:
    //returns the position that the entity would be in after moving
    void move( int& newPosX, int& newPosY );
    void setPosition( float posx, float posy );
    
    bool checkCollision( int posx, int posy );
    
    int getX();
    int getY();
    
    void setDirection( int direction );
    void draw( Engine::VideoDriver* videoDriver );
    
    void takeDamage( int damage );
    int getHealth();
    void setHealth( int value );
    
protected:
    float posx, posy;
    int direction;
    float speed;
    int textureIndex;
    int health = 100;
};

