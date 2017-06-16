#include "Screen.h"

using namespace Screens;

void Screen::renderFrame( Engine::VideoDriver* videoDriver )
{
    videoDriver->clearWindow( sf::Color( 20, 60, 255 ) );
    uiManager->drawUI( videoDriver );
    videoDriver->displayWindow();
}

void Screen::handleClick( int mouseX, int mouseY )
{
    uiManager->handleClick( mouseX, mouseY );
}