#pragma once

#include <string>
#include "UIElement.h"
#include "UILabel.h"

namespace UI {
    
class UIButton : public UIElement {
public:
    UIButton( int posx, int posy, 
              int width, int height, 
              sf::Color bgColor, std::string text, 
              int onClickSignal );
    
    UIButton();
    
    virtual void onClick();
    virtual void draw( Engine::VideoDriver* videoDriver );
    
    void setButtonTextSize( int size );
    
    void setPosition( int posx, int posy );
    
protected:
    UILabel message;
};

}


