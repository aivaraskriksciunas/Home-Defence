#pragma once
#include "UIElement.h"

namespace UI {
    
class UIProgressBar : public UIElement {
public:
    UIProgressBar( int posx, int posy, int width, int height, int maxValue, sf::Color bgColor );
    void draw( Engine::VideoDriver* videoDriver );
    
    void setValue( int value );
    void setMaxValue( int value );
    
private:
    int maxValue;
    float value;
    
    int calculateBarLength();
};

}


