#include "GameStateBuild.h"

using namespace GameStates;

GameStateBuild::GameStateBuild( World::WorldManager* worldManager, int windowWidth, int windowHeight )
{
    this->worldManager = worldManager;
    this->screen = new Screens::GameBuildScreen( windowWidth, windowHeight );
}


void GameStateBuild::update( int timeLeft, int money )
{
    this->screen->updateUI( timeLeft, money );
}

void GameStateBuild::draw( Engine::VideoDriver* videoDriver )
{
    this->screen->renderFrame( videoDriver, worldManager );
}

void GameStateBuild::reset()
{
    
}

void GameStateBuild::handleMouseClick( int mouseX, int mouseY )
{
    if ( screen->handleClick( mouseX, mouseY ) )
        return; //mouse click was handled in uimanager, so do not continue
    
    
}