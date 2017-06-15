#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
class VideoDriver
{
public:
    VideoDriver( sf::RenderWindow* window );
    void drawTexture( sf::Texture& texture, int posx, int posy );
    void drawRectangle( sf::Color color, int posx, int posy, int width, int height );
    void drawText( sf::Font& font, sf::Color color, std::string text, 
                    int posx, int posy, 
                    int characterSize );
    
    int getWindowWidth();
    int getWindowHeight();
    
private:
    sf::RenderWindow* windowPtr;  
};
}


