#pragma once 

#include "../engine/VideoDriver.h"
#include "../engine/SignalManager.h"
#include "SFML/Graphics.hpp"

namespace UI {
    
class UIElement {        
public:
    
    virtual void onClick();
    void setOnClickSignal( int signal );
    
    virtual void draw( Engine::VideoDriver* videoDriver ) = 0;
    
    virtual void setPosition( int posx, int posy );
    void setSize( int width, int height );
    void setBgColor( sf::Color color );
    
    int getPositionX();
    int getPositionY();
    
    bool posInsideElement( int x, int y );
    
    static void setLastMousePos( int mouseX, int mouseY );
    
    void setVisible( bool value );
    bool isVisible();
    
protected:
    int posx, posy;
    int width, height;
    sf::Color bgColor;
    
    static int lastMousePosX, lastMousePosY;
    
    int onClickSignal;
    
    bool visible = true;
};

}
