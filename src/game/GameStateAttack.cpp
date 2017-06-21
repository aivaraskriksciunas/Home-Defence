#include "GameStateAttack.h"

using namespace GameStates;

GameStateAttack::GameStateAttack( World::WorldManager* worldManager, int windowWidth, int windowHeight )
{
    this->worldManager = worldManager;
    
    this->gameLevel = 1;
    this->ammo = STARTING_AMMO;
    this->wallRepairs = STARTING_WALL_REPAIRS;
    this->worldManager->calculateLevelEnemyCount( this->gameLevel );
    
    this->screen = new Screens::GameAttackScreen( windowWidth, windowHeight );
}


void GameStateAttack::update( int timeLeft )
{
    this->screen->updateUI( this->ammo, this->wallRepairs, 
                            worldManager->getPlayerHealth(), worldManager->getGemHealth(),
                            timeLeft );
}

void GameStateAttack::draw( Engine::VideoDriver* videoDriver )
{
    this->screen->renderFrame( videoDriver, worldManager );
}

void GameStateAttack::reset()
{
    this->ammo = 50;
    this->wallRepairs = 10;
    
    //initialize clocks 
    this->enemyMoveClock.restart();
    this->gemDamageClock.restart();
}

void GameStateAttack::handleMouseClick( int mouseX, int mouseY,
                                        int windowMiddleX, int windowMiddleY )
{
    if ( ammo > 0 )
    {
        float direction = std::atan2( mouseY - windowMiddleY,
                                      mouseX - windowMiddleX );

        direction *= 180 / M_PI; //convert to degrees

        worldManager->shoot( direction );

        ammo--;
    }
}

void GameStateAttack::fixWall()
{
    if ( wallRepairs > 0 )
    {
        if ( worldManager->fixWall() )
            wallRepairs--;
    }
}

void GameStateAttack::addAmmo( int amount )
{
    this->ammo += amount;
}

void GameStateAttack::addWallRepairs( int amount )
{
    this->wallRepairs += amount;
}

void GameStateAttack::handleTimers( )
{
    if ( enemyMoveClock.getElapsedTime().asMilliseconds() >= enemyMoveIntervalMs )
    {
        worldManager->updateEnemies();
        worldManager->updateBullets();
        enemyMoveClock.restart();
    }
    if ( gemDamageClock.getElapsedTime().asMilliseconds() >= gemDamageIntervalMs )
    {
        worldManager->updateGem();
        gemDamageClock.restart();
    }
}

void GameStateAttack::increaseLevel()
{
    this->gameLevel++;
    worldManager->calculateLevelEnemyCount( gameLevel );
    //make sure player has enough ammo and wall repairs to begin next level
    if ( ammo < STARTING_AMMO )
    {
        ammo = STARTING_AMMO;
    }
    
    if ( wallRepairs < STARTING_WALL_REPAIRS )
    {
        wallRepairs = STARTING_WALL_REPAIRS;
    }
    
    this->worldManager->setPlayerHealth( 100 );
            
    //initialize clocks 
    this->enemyMoveClock.restart();
    this->gemDamageClock.restart();
}