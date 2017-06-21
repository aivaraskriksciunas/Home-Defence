#include "GameBuildScreen.h"

using namespace Screens;

GameBuildScreen::GameBuildScreen( int windowWidth, int windowHeight )
{
    this->infoBox = new UI::UIBox( 0, 0, 100, 100 );
    this->timeBox = new UI::UIBox( windowWidth - 80, 0, 80, 30 );
    this->timeLabel = new UI::UILabel( 10, 5, "00:00", sf::Color::White, FONT_SIMPLE, 17 );
    this->timeBox->addElement( timeLabel );
    
    this->moneyLabel = new UI::UILabel( 5, 10, "Money: 0", sf::Color::White, FONT_SIMPLE, 17 );
    
    this->infoBox->addElement( moneyLabel );
    
    int startAttackBtnWidth = 90, startAttackBtnHeight = 30;
    this->startAttackButton = new UI::UIButton( windowWidth - startAttackBtnWidth, 50,
                                                startAttackBtnWidth, startAttackBtnHeight,
                                                sf::Color( 100, 150, 100, 255 ),
                                                "Start >>",
                                                SIG_BEGIN_ATTACK );
    
    this->uiManager.AddElement( infoBox );
    this->uiManager.AddElement( timeBox );
    this->uiManager.AddElement( startAttackButton );
    
    this->mainViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setCenter( windowWidth / 2, windowHeight / 2 );
}

void GameBuildScreen::updateUI( int timeLeft, int money )
{
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;
    
    std::stringstream text;
    text << minutes << ":" << seconds;
    this->timeLabel->setText( text.str() );
    
    text.str( "" );
    text << "Money: " << money;
    this->moneyLabel->setText( text.str() );
}

void GameBuildScreen::renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager )
{
    videoDriver->clearWindow( sf::Color::Black );
    
    this->mainViewport.setCenter( worldManager->getPlayerX(), worldManager->getPlayerY() );
    
    videoDriver->setView( this->mainViewport );
    worldManager->draw( videoDriver );
    
    videoDriver->setView( this->uiViewport );
    this->uiManager.drawUI( videoDriver );
    
    videoDriver->displayWindow();
    
}