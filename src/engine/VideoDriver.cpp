#include "VideoDriver.h"

using namespace Engine;

VideoDriver::VideoDriver( sf::RenderWindow* window ) : windowPtr( window ) {}

void VideoDriver::drawTexture( sf::Texture& texture, int posx, int posy )
{
    
    sf::Sprite textureSprite;

    textureSprite.setTexture( texture );
    textureSprite.setPosition( posx, posy );

    this->windowPtr->draw( textureSprite );
    
}

int VideoDriver::getWindowHeight()
{
    return this->windowPtr->getSize().y;
}

int VideoDriver::getWindowWidth()
{
    return this->windowPtr->getSize().x;
}

