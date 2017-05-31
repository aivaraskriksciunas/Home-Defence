#include "VideoDriver.h"

using namespace Engine;

VideoDriver::VideoDriver( sf::RenderWindow* window ) : windowPtr( window ) {}

void VideoDriver::drawTexture( sf::Texture& texture, int posx, int posy )
{
    //check if texture will be visible in the screen, if not then don't draw it
    if ( posx + (int)texture.getSize().x > 0 && posx < (int)this->windowPtr->getSize().x )
    {
        if ( posy + (int)texture.getSize().y > 0 && posy < (int)this->windowPtr->getSize().y )
        {
            sf::Sprite textureSprite;
    
            textureSprite.setTexture( texture );
            textureSprite.setPosition( posx, posy );

            this->windowPtr->draw( textureSprite );
        }
    }
    
}

