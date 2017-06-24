#include "GameBuildScreen.h"

using namespace Screens;

GameBuildScreen::GameBuildScreen( int windowWidth, int windowHeight )
{
    this->storeManager = new GameStoreManager( &uiManager, windowWidth, windowHeight );
    
    this->infoBox = new UI::UIBox( 0, 0, 100, 100 );
    
    this->moneyLabel = new UI::UILabel( 5, 10, "Money: 0", sf::Color::White, FONT_SIMPLE, 17 );
    
    this->infoBox->addElement( moneyLabel );
    
    int startAttackBtnWidth = 90, startAttackBtnHeight = 30;
    this->startAttackButton = new UI::UIButton( windowWidth - startAttackBtnWidth, 50,
                                                startAttackBtnWidth, startAttackBtnHeight,
                                                sf::Color( 100, 150, 100, 255 ),
                                                "Start >>",
                                                SIG_BEGIN_ATTACK );
    
    
    this->uiManager.AddElement( infoBox );
    this->uiManager.AddElement( startAttackButton );
    
    this->mainViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setCenter( windowWidth / 2, windowHeight / 2 );
}

void GameBuildScreen::updateUI( int money )
{
    storeManager->updateUI();
    
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

int GameBuildScreen::getBuildMode()
{
    return storeManager->getBuildMode();
}

int GameBuildScreen::getSelectedWallType()
{
    return storeManager->getSelectedWall();
}

int GameBuildScreen::getSelectedWallCost( int wallType )
{
    return storeManager->getSelectedWallCost( wallType );
}

int GameBuildScreen::getSelectedDefence()
{
    return storeManager->getSelectedDefence();
}

int GameBuildScreen::getSelectedDefenceCost( int defenceType )
{
    return storeManager->getSelectedDefenceCost( defenceType );
}