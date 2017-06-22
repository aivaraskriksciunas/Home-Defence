#include "UIElement.h"

using namespace UI;

int UIElement::lastMousePosX;
int UIElement::lastMousePosY;

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

void UIElement::onClick() {}

bool UIElement::posInsideElement( int x, int y )
{
    if ( x >= this->posx && x <= this->posx + this->width )
    {
        if ( y >= this->posy && y <= this->posy + this->height )
        {
            return true;
        }
    }
    
    return false;
}

void UIElement::setOnClickSignal( int signal )
{
    this->onClickSignal = signal;
}

void UIElement::setLastMousePos( int mouseX, int mouseY )
{
    lastMousePosX = mouseX;
    lastMousePosY = mouseY;
}