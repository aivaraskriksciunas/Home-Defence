#include "UIBox.h"

using namespace UI;

UIBox::UIBox( int posx, int posy, int width, int height, sf::Color bgColor )
{
    this->posx = posx;
    this->posy = posy;
    this->width = width;
    this->height = height;
    this->bgColor = bgColor;
}

void UIBox::draw( Engine::VideoDriver* videoDriver )
{
    //draw box
    videoDriver->drawRectangle( this->bgColor,
                                this->posx, this->posy, 
                                this->width, this->height );
    
    //draw all the elements inside it
    for ( int uiIndex = 0; uiIndex < uiElements.size(); uiIndex++ )
    {
        uiElements[uiIndex]->draw( videoDriver );
    }
}

void UIBox::addElement( UIElement* element )
{
    //set the position relative to screen instead of parent object
    element->setPosition( element->getPositionX() + posx,
                          element->getPositionY() + posy );
    this->uiElements.push_back( element );
}