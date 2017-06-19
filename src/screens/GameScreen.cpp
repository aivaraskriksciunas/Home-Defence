#include "GameScreen.h"

using namespace Screens;

GameScreen::GameScreen( int windowWidth, int windowHeight )
{
    this->infoBox = new UI::UIBox( 0, 0, 100, 100 );
    
    this->healthIcon = new UI::UIIcon( 5, 10, TEXTURE_ICON_HEART );
    this->healthLabel = new UI::UIProgressBar( 30, 10, maxProgressBarLength, 10, 100, sf::Color::Red );
    this->gemIcon = new UI::UIIcon( 5, 30, TEXTURE_ICON_GEM );
    this->gemLabel = new UI::UIProgressBar( 30, 30, maxProgressBarLength, 10, 100, sf::Color::Red );
    this->ammoIcon = new UI::UIIcon( 5, 50, TEXTURE_ICON_BULLET );
    this->ammoLabel = new UI::UILabel( 30, 50, "0 ", sf::Color::White, FONT_SIMPLE, 17 );
    this->repairIcon = new UI::UIIcon( 5, 70, TEXTURE_ICON_HAMMER );
    this->repairLabel = new UI::UILabel( 30, 70, "0", sf::Color::White, FONT_SIMPLE, 17 );
    
    this->infoBox->addElement( healthLabel );
    this->infoBox->addElement( healthIcon );
    this->infoBox->addElement( gemIcon );
    this->infoBox->addElement( gemLabel );
    this->infoBox->addElement( ammoLabel );
    this->infoBox->addElement( ammoIcon );
    this->infoBox->addElement( repairIcon );
    this->infoBox->addElement( repairLabel );
    
    this->uiManager.AddElement( infoBox );
    
    this->mainViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setSize( windowWidth, windowHeight );
    this->uiViewport.setCenter( windowWidth / 2, windowHeight / 2 );
}

void GameScreen::updateUI( int ammo, int wallRepairs, int playerHealth, int gemHealth )
{
    std::stringstream text( "" );
    text << ammo;
    this->ammoLabel->setText( text.str() );
    
    text.str( "" );
    text << wallRepairs;
    this->repairLabel->setText( text.str() );
    
    this->healthLabel->setValue( playerHealth );
    this->gemLabel->setValue( gemHealth );
}

void GameScreen::renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager )
{
    videoDriver->clearWindow( sf::Color::Black );
    
    this->mainViewport.setCenter( worldManager->getPlayerX(), worldManager->getPlayerY() );
    
    videoDriver->setView( this->mainViewport );
    worldManager->draw( videoDriver );
    
    videoDriver->setView( this->uiViewport );
    this->uiManager.drawUI( videoDriver );
    
    videoDriver->displayWindow();
    
}