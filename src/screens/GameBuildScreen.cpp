#include "GameBuildScreen.h"

using namespace Screens;

GameBuildScreen::GameBuildScreen( int windowWidth, int windowHeight )
{
    this->infoBox = new UI::UIBox( 0, 0, 100, 100 );
    
    this->moneyLabel = new UI::UILabel( 5, 10, "Money: 0", sf::Color::White, FONT_SIMPLE, 17 );
    
    this->infoBox->addElement( moneyLabel );
    
    int startAttackBtnWidth = 90, startAttackBtnHeight = 30;
    this->startAttackButton = new UI::UIButton( windowWidth - startAttackBtnWidth, 50,
                                                startAttackBtnWidth, startAttackBtnHeight,
                                                sf::Color( 100, 150, 100, 255 ),
                                                "Start >>",
                                                SIG_BEGIN_ATTACK );
    
    this->actionButtonContainer = new UI::UISelectButtonContainer( 0, windowHeight - actionContainerHeight,
                                                                  actionContainerWidth, actionContainerHeight,
                                                                  sf::Color( 150, 150, 150, 255 ) );
    this->actionBuildBtn = new UI::UISelectButton( 0, 0, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Build",
                                                   SIG_NULL );
    this->actionRebuildWallsBtn = new UI::UISelectButton( 0, 30, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Rebuild Walls",
                                                   SIG_REBUILD_WALLS );
    this->actionBuyDefensesBtn = new UI::UISelectButton( 0, 60, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Buy Defenses",
                                                   SIG_NULL );
    
    this->actionButtonContainer->addButton( actionBuildBtn );
    this->actionButtonContainer->addButton( actionRebuildWallsBtn );
    this->actionButtonContainer->addButton( actionBuyDefensesBtn );
    this->actionButtonContainer->setButtonsTextSize( 12 );
    
    this->uiManager.AddElement( infoBox );
    this->uiManager.AddElement( startAttackButton );
    this->uiManager.AddElement( actionButtonContainer );
    
    this->mainViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setCenter( windowWidth / 2, windowHeight / 2 );
}

void GameBuildScreen::updateUI(  int money )
{
    std::stringstream text;
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