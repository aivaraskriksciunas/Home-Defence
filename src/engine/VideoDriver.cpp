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

void VideoDriver::drawTexture( sf::Texture& texture, int posx, int posy, float width, float height )
{
    sf::Sprite textureSprite;

    textureSprite.setTexture( texture );
    textureSprite.setPosition( posx, posy );
    textureSprite.setScale( width / texture.getSize().x, 
                            height / texture.getSize().y );

    this->windowPtr->draw( textureSprite );
    
}

void VideoDriver::drawTexture( sf::Texture& texture, int posx, int posy, sf::Color textureColor )
{
    sf::Sprite textureSprite;

    textureSprite.setTexture( texture );
    textureSprite.setPosition( posx, posy );
    textureSprite.setColor( textureColor );

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

void VideoDriver::drawTextCentered( sf::Font& font, sf::Color color, std::string textString, 
                                    int posx, int posy, 
                                    int characterSize )
{
    sf::Text text;
    text.setFont( font );
    text.setFillColor( color );
    text.setString( sf::String( textString.c_str() ) );
    text.setCharacterSize( characterSize );
    
    text.setOrigin( text.getGlobalBounds().width / 2,
                    text.getGlobalBounds().height / 2 );
    text.setPosition( posx, posy );
    
    this->windowPtr->draw( text );
}

void VideoDriver::clearWindow( sf::Color clearColor )
{
    this->windowPtr->clear( clearColor );
}

void VideoDriver::displayWindow()
{
    this->windowPtr->display();
}

int VideoDriver::getWindowHeight()
{
    return this->windowPtr->getSize().y;
}

int VideoDriver::getWindowWidth()
{
    return this->windowPtr->getSize().x;
}

void VideoDriver::setView( sf::View& view )
{
    this->windowPtr->setView( view );
}