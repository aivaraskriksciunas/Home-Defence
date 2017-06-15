#pragma once

#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"

namespace UI {
    
class UIIcon : public UIElement {
public:
    UIIcon( int posx, int posy, int textureID );
    UIIcon();
    
    void draw( Engine::VideoDriver* videoDriver );
    
private:
    int textureID;
};

}

