#include "PauseScreen.h"

using namespace Screens;

PauseScreen::PauseScreen( int windowWidth, int windowHeight )
{
    this->title = UI::UILabel( windowWidth / 2, 100, "Paused", sf::Color::White, FONT_SIMPLE, 30 );
    this->title.setCentered( true );
    
    this->startButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 300, 
                                      buttonWidth, buttonHeight, 
                                      sf::Color( 120, 120, 120, 255 ), "Resume", 
                                      SIG_GAME_RESUME );
    this->restartButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 400, 
                                      buttonWidth, buttonHeight, 
                                      sf::Color( 120, 120, 120, 255 ), "Restart", 
                                      SIG_GAME_RESTART );
    this->quitButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 500, 
                                     buttonWidth, buttonHeight, 
                                     sf::Color( 120, 120, 120, 255 ), "Main Menu", 
                                     SIG_GAME_STATE_MENU );
    
    uiManager.AddElement( &title );
    uiManager.AddElement( &startButton );
    uiManager.AddElement( &restartButton );
    uiManager.AddElement( &quitButton );
}


