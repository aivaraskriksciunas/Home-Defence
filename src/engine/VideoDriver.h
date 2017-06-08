#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
class VideoDriver
{
public:
    VideoDriver( sf::RenderWindow* window );
    void drawTexture( sf::Texture& texture, int posx, int posy );
    
    int getWindowWidth();
    int getWindowHeight();
    
private:
    sf::RenderWindow* windowPtr;  
};
}


