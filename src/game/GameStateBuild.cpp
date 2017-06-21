#include "GameStateBuild.h"

using namespace GameStates;

GameStateBuild::GameStateBuild( World::WorldManager* worldManager, int windowWidth, int windowHeight )
{
    this->worldManager = worldManager;
    this->screen = new Screens::GameBuildScreen( windowWidth, windowHeight );
}


void GameStateBuild::update( int timeLeft )
{
    this->screen->updateUI( timeLeft );
}

void GameStateBuild::draw( Engine::VideoDriver* videoDriver )
{
    this->screen->renderFrame( videoDriver, worldManager );
}

void GameStateBuild::reset()
{
    
}