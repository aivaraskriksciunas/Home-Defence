#pragma once

#include "UIElement.h"
#include "UILabel.h"
#include "UIButton.h"

namespace UI {
class UISelectButton : public UIButton {
public:
    UISelectButton( int posx, int posy, int width, int height, 
                    sf::Color bgColor, sf::Color selectColor,
                    std::string text, int selectSignal );
    
    void draw( Engine::VideoDriver* videoDriver );
    
    void onClick();
    void setSelected( bool value );
    bool isSelected();
    
private:
    sf::Color selectColor;
    
    bool selected;
    
};

}

