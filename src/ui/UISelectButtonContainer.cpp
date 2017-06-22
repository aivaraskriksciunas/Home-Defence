#include "UISelectButtonContainer.h"

using namespace UI;

UISelectButtonContainer::UISelectButtonContainer( int posx, int posy, int width, int height, sf::Color bgColor )
{
    this->posx = posx;
    this->posy = posy;
    this->width = width;
    this->height = height;
    this->bgColor = bgColor;
}

void UISelectButtonContainer::draw( Engine::VideoDriver* videoDriver ) 
{
    videoDriver->drawRectangle( bgColor, posx, posy, width, height );
    
    for ( int elementIndex = 0; elementIndex < buttons.size(); elementIndex++ )
    {
        buttons[elementIndex]->draw( videoDriver );
    }
}

void UISelectButtonContainer::addButton( UISelectButton* button ) 
{
    button->setPosition( button->getPositionX() + posx, button->getPositionY() + posy );
    this->buttons.push_back( button );
}

void UISelectButtonContainer::onClick()
{
    for ( int btnIndex = 0; btnIndex < buttons.size(); btnIndex++ )
    {
        if ( buttons[btnIndex]->posInsideElement( lastMousePosX, lastMousePosY ) )
        {
            buttons[btnIndex]->onClick();
        }
        else 
        {
            buttons[btnIndex]->setSelected( false );
        }
    }
}

void UISelectButtonContainer::setButtonsTextSize(int size)
{
    for ( int btnIndex = 0; btnIndex < buttons.size(); btnIndex++ )
    {
        buttons[btnIndex]->setButtonTextSize( size );
    }
}