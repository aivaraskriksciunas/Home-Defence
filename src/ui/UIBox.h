#pragma once
#include "UIElement.h"
#include <vector>

namespace UI {

class UIBox : public UIElement {
public:
    UIBox( int posx, int posy, int width, int height,
           sf::Color bgColor = { 130, 130, 130, 200 } );
    UIBox();
    
    void draw( Engine::VideoDriver* videoDriver );
    void addElement( UIElement* element );
    
private:
    std::vector<UIElement*> uiElements;
     
};
}


