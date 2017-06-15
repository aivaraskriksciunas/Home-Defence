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

void VideoDriver::drawRectangle( sf::Color color, int posx, int posy, int width, int height )
{
    sf::RectangleShape rect;
    rect.setFillColor( color );
    rect.setPosition( posx, posy );
    rect.setSize( sf::Vector2f( width, height ) );
    
    this->windowPtr->draw( rect );
}

void VideoDriver::drawText( sf::Font& font, sf::Color color, std::string textString, 
                            int posx, int posy, 
                            int characterSize )
{
    sf::Text text;
    text.setFont( font );
    text.setPosition( posx, posy );
    text.setFillColor( color );
    text.setString( sf::String( textString.c_str() ) );
    text.setCharacterSize( characterSize );
    
    this->windowPtr->draw( text );
}

int VideoDriver::getWindowHeight()
{
    return this->windowPtr->getSize().y;
}

int VideoDriver::getWindowWidth()
{
    return this->windowPtr->getSize().x;
}

