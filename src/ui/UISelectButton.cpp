#include "UISelectButton.h"

using namespace UI;

UISelectButton::UISelectButton( int posx, int posy, int width, int height, 
                                sf::Color bgColor, sf::Color selectColor,
                                std::string text, int selectSignal )
    : UIButton( posx, posy, width, height, bgColor, text, selectSignal ) //call parent constructor
{
    this->selected = false;
    
    this->selectColor = selectColor;
}

void UISelectButton::draw( Engine::VideoDriver* videoDriver )
{
    if ( selected )
    {
        videoDriver->drawRectangle( selectColor, posx, posy, width, height );
    }
    else
    {
        videoDriver->drawRectangle( bgColor, posx, posy, width, height );
    }
    
    message.draw( videoDriver );
}

void UISelectButton::onClick()
{
    selected = !selected;
    Engine::SignalManager::sendSignal( onClickSignal );
}

void UISelectButton::setSelected( bool value ) 
{
    selected = value;
}


