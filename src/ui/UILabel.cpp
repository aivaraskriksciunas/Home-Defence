#include "UILabel.h"

using namespace UI;

UILabel::UILabel( int posx, int posy, std::string text, sf::Color color, int fontID, int characterSize )
{
    this->posx = posx;
    this->posy = posy;
    this->text = text;
    this->bgColor = color;
    this->fontID = fontID;
    this->characterSize = characterSize;
    this->textCentered = false;
}

UILabel::UILabel() {}

void UILabel::draw( Engine::VideoDriver* videoDriver )
{
    if ( textCentered )
    {
        videoDriver->drawTextCentered( Engine::TextureManager::getFont( FONT_SIMPLE ),
                                       this->bgColor, 
                                       this->text,
                                       this->posx, this->posy,
                                       this->characterSize );
    }
    else
    {
        videoDriver->drawText( Engine::TextureManager::getFont( FONT_SIMPLE ),
                               this->bgColor, 
                               this->text,
                               this->posx, this->posy,
                               this->characterSize );
    }
}

void UILabel::setCharacterSize( int size )
{
    this->characterSize = size;
}

void UILabel::setText( std::string text )
{
    this->text = text;
}

void UILabel::setCentered( bool center )
{
    this->textCentered = center;
}