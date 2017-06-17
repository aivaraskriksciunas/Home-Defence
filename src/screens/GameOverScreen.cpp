#include "GameOverScreen.h"

using namespace Screens;

GameOverScreen::GameOverScreen( int windowWidth, int windowHeight )
{
    this->title = UI::UILabel( windowWidth / 2, 100, "Game Over!", sf::Color::White, FONT_SIMPLE, 30 );
    this->title.setCentered( true );
    
    this->restartButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 300, 
                                      buttonWidth, buttonHeight, 
                                      sf::Color( 120, 120, 120, 255 ), "Restart", 
                                      SIG_GAME_RESTART );
    this->menuButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 400, 
                                     buttonWidth, buttonHeight, 
                                     sf::Color( 120, 120, 120, 255 ), "Main Menu", 
                                     SIG_GAME_STATE_MENU );
    this->quitButton = UI::UIButton( windowWidth / 2 - buttonWidth / 2, 500, 
                                     buttonWidth, buttonHeight, 
                                     sf::Color( 120, 120, 120, 255 ), "Quit", 
                                     SIG_QUIT );
    
    uiManager.AddElement( &title );
    uiManager.AddElement( &restartButton );
    uiManager.AddElement( &menuButton );
    uiManager.AddElement( &quitButton );
}


