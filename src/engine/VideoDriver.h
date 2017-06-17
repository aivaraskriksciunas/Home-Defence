#pragma once
#include "SFML/Graphics.hpp"

namespace Engine {
class VideoDriver
{
public:
    VideoDriver( sf::RenderWindow* window );
    void drawTexture( sf::Texture& texture, int posx, int posy );
    void drawTexture( sf::Texture& texture, int posx, int posy, float width, float height );
    
    void drawRectangle( sf::Color color, int posx, int posy, int width, int height );
    void drawText( sf::Font& font, sf::Color color, std::string text, 
                    int posx, int posy, 
                    int characterSize );
    
    void clearWindow( sf::Color clearColor );
    void displayWindow();
    void setView( sf::View& view );
    
    int getWindowWidth();
    int getWindowHeight();
    
private:
    sf::RenderWindow* windowPtr;  
};
}


