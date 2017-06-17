#include "StartScreen.h"

using namespace Screens;

StartScreen::StartScreen( int windowWidth, int windowHeight )
{
    this->title = UI::UILabel( windowWidth / 2, 100, "Home Defence", sf::Color::White, FONT_SIMPLE, 25 );
    this->title.setCentered( true );
    
    this->startButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 300, 
                                      buttonWidth, buttonHeight, 
                                      sf::Color( 120, 120, 120, 255 ), "Start Game", 
                                      SIG_GAME_RESTART );
    this->quitButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 400, 
                                     buttonWidth, buttonHeight, 
                                     sf::Color( 120, 120, 120, 255 ), "Quit", 
                                     SIG_QUIT );
    
    uiManager.AddElement( &title );
    uiManager.AddElement( &startButton );
    uiManager.AddElement( &quitButton );
}


