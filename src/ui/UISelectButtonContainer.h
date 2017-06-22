#pragma once

#include "UIElement.h"
#include "UISelectButton.h"
#include <vector>

namespace UI {
    
class UISelectButtonContainer : public UIElement {
public:
    UISelectButtonContainer( int posx, int posy, int width, int height, sf::Color bgColor );
    
    void draw( Engine::VideoDriver* videoDriver );
    void onClick();
    
    void addButton( UISelectButton* button );
    
    void setButtonsTextSize( int size );
    
private:
    std::vector<UISelectButton*> buttons;
};

}

