#pragma once 

#include <vector>
#include "../ui/UIElement.h"
#include "../ui/UIManager.h"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"

namespace Screens {
class Screen {
public:
    virtual void renderFrame( Engine::VideoDriver* videoDriver );
    virtual void handleClick( int mouseX, int mouseY );
    
protected:
    UI::UIManager* uiManager;
    
};
}

