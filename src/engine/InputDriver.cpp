#include "InputDriver.h"

using namespace Engine;

void InputDriver::handleInput( sf::RenderWindow* window )
{
    sf::Event event;
    while ( window->pollEvent( event ) )
    {
        if ( event.type == sf::Event::Closed )
        {
            SignalManager::sendSignal( SIG_QUIT );
        }
    }
    
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        SignalManager::sendSignal( SIG_MAP_SCROLL_LEFT );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        SignalManager::sendSignal( SIG_MAP_SCROLL_RIGHT );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        SignalManager::sendSignal( SIG_MAP_SCROLL_UP );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        SignalManager::sendSignal( SIG_MAP_SCROLL_DOWN );
    }
}


