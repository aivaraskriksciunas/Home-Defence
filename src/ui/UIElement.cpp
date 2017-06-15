#include "UIElement.h"

using namespace UI;

void UIElement::setBgColor( sf::Color color )
{
    this->bgColor = color;
}

void UIElement::setPosition( int posx, int posy )
{
    this->posx = posx;
    this->posy = posy;
}

void UIElement::setSize( int width, int height )
{
    this->width = width;
    this->height = height;
}

int UIElement::getPositionX()
{
    return this->posx;
}

int UIElement::getPositionY()
{
    return this->posy;
}

void UIElement::addElement( UIElement* element ) {}