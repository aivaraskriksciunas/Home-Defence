#pragma once 

#include <string>
#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include "../engine/VideoDriver.h"
#include "../engine/TextureManager.h"

namespace UI {
    
class UILabel : public UIElement {
public:
    UILabel( int posx, int posy, std::string text, sf::Color color, int fontID, int characterSize = 20 );
    UILabel();
    void draw( Engine::VideoDriver* videoDriver );
    
    void setCharacterSize( int size );
    
    void setText( std::string text );
    
private:
    std::string text;
    int fontID;
    
    int characterSize;
};

}

