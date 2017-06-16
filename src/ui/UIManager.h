#pragma once

#include <vector>
#include "UIElement.h"
#include "UIBox.h"
#include "../engine/VideoDriver.h"

namespace UI {
    
class UIManager {
public:
    UIManager();
    void AddElement( UIElement* element );
    void drawUI( Engine::VideoDriver* videoDriver );
    
    bool handleClick( int mouseX, int mouseY );
    
private:
    std::vector<UIElement*> uiElements;
    
};

}
