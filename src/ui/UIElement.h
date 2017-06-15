#pragma once 

#include "../engine/VideoDriver.h"
#include "../engine/SignalManager.h"
#include "SFML/Graphics.hpp"

namespace UI {
    
class UIElement {        
public:
    
    //virtual void onClick();
    //virtual void onHover();
    //virtual void onRelease();
    
    virtual void draw( Engine::VideoDriver* videoDriver ) = 0;
    virtual void addElement( UIElement* element );
    
    void setPosition( int posx, int posy );
    void setSize( int width, int height );
    void setBgColor( sf::Color color );
    
    int getPositionX();
    int getPositionY();
    
protected:
    int posx, posy;
    int width, height;
    sf::Color bgColor;
    
    int onClickSignal;
};

}
