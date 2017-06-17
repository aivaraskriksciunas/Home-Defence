#include "StartScreen.h"

using namespace Screens;

StartScreen::StartScreen()
{
    this->title = UI::UILabel( 100, 100, "Home Defence", sf::Color::White, FONT_SIMPLE, 25 );
    
    this->startButton = UI::UIButton( 100, 300, 200, 50, sf::Color( 120, 120, 120, 0 ), "Start Game", SIG_GAME_RESTART );
    this->quitButton = UI::UIButton( 100, 400, 200, 50, sf::Color( 120, 120, 120, 255 ), "Quit", SIG_QUIT );
    
    uiManager.AddElement( &title );
    uiManager.AddElement( &startButton );
    uiManager.AddElement( &quitButton );
}


