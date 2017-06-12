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
        else if ( event.type == sf::Event::MouseButtonPressed )
        {
            SignalManager::sendSignal( SIG_MOUSE_LEFT_CLICK );
        }
        else if ( event.type == sf::Event::KeyPressed )
        {
            switch ( event.key.code )
            {
            case sf::Keyboard::Space:
                SignalManager::sendSignal( SIG_KEY_SPACE_PRESS );
                break;
            }
        }
    }
    
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) &&
              sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_NE );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && 
              sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_SW );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) &&
              sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_SE );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && 
              sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_NW );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_N );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_E );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_S );
    }
    else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        SignalManager::sendSignal( SIG_PLAYER_MOVE_W );
    }
}


