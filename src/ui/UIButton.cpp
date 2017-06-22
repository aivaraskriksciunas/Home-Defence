#include "UIButton.h"

using namespace UI;

UIButton::UIButton( int posx, int posy, int width, int height, sf::Color bgColor, std::string text, int onClickSignal )
{
    this->posx = posx;
    this->posy = posy;
    this->width = width;
    this->height = height;
    this->bgColor = bgColor;
    this->message = UILabel( posx + width / 2, posy + height / 2,
                             text, 
                             sf::Color::White,
                             FONT_SIMPLE, 15 );
    
    this->message.setCentered( true );
    
    this->onClickSignal = onClickSignal;
}

UIButton::UIButton( ) {}

void UIButton::onClick()
{
    Engine::SignalManager::sendSignal( this->onClickSignal );
}
    
void UIButton::draw( Engine::VideoDriver* videoDriver ) 
{
    videoDriver->drawRectangle( this->bgColor, 
                                 this->posx, this->posy, 
                                 this->width, this->height );
    
    this->message.draw( videoDriver );
}

void UIButton::setButtonTextSize( int size )
{
    this->message.setCharacterSize( size );
}

void UIButton::setPosition( int posx, int posy ) 
{
    this->posx = posx;
    this->posy = posy;
    
    this->message.setPosition( this->posx + this->width / 2, this->posy + this->height / 2 );
}