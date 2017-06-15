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
}

void UILabel::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawText( Engine::TextureManager::getFont( FONT_SIMPLE ),
                           this->bgColor, 
                           this->text,
                           this->posx, this->posy,
                           this->characterSize );
}

void UILabel::setCharacterSize( int size )
{
    this->characterSize = size;
}

void UILabel::setText( std::string text )
{
    this->text = text;
}
