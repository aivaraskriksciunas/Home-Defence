#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
class VideoDriver
{
public:
    VideoDriver( sf::RenderWindow* window );
    void drawTexture( sf::Texture& texture, int posx, int posy );
    
private:
    sf::RenderWindow* windowPtr;  
};
}


