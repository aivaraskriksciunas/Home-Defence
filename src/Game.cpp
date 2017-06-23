#include "Game.h"
#include "ui/UIIcon.h"

using namespace Engine;

Game::Game( char* programPath, char* title, int width, int height ) : 
    windowWidth( width ), windowHeight( height ) 
{
    
    this->mainWindow = new sf::RenderWindow( sf::VideoMode( this->windowWidth, this->windowHeight ),
                                             title,
                                             sf::Style::Default );
    
    this->mainWindow->setFramerateLimit( 80 );
    
    //get only the path to the file without the file name
    this->programPathWithoutName = getPathWithoutFileName( programPath );
    
    //initialize drivers and managers
    this->videoDriver = new Engine::VideoDriver( this->mainWindow );
    this->textureManager = new Engine::TextureManager( programPathWithoutName );
    this->inputDriver = new Engine::InputDriver();
    this->worldManager = new World::WorldManager();
    
    this->startScreen = new Screens::StartScreen( windowWidth, windowHeight );
    this->pauseScreen = new Screens::PauseScreen( windowWidth, windowHeight );
    this->gameOverScreen = new Screens::GameOverScreen( windowWidth, windowHeight );
    
    this->buildState = new GameStates::GameStateBuild( worldManager, windowWidth, windowHeight );
    this->attackState = new GameStates::GameStateAttack( worldManager, windowWidth, windowHeight );
    
    this->money = 0;
    
    this->gameState = STATE_START_SCREEN;
}

void Game::handleSignals()
{
    int signal = 0;
    while ( SignalManager::pollSignal( signal ) )
    {
        if ( signal == SIG_QUIT || signal == SIG_ERROR || signal == SIG_RESOURCE_LOAD_ERROR )
        {
            gameState = STATE_QUIT;
        }
        else if ( signal == SIG_TEXTURE_LOAD_ERROR )
        {
            gameState = STATE_QUIT;
            this->texturesLoaded = false;
        }
        else if ( signal == SIG_GAME_RESTART )
        {
            resetGame();
            gameState = STATE_RUNNING;
        }
        else if ( signal == SIG_GAME_RESUME )
        {
            gameState = STATE_RUNNING;
        }
        else if ( signal == SIG_GAME_STATE_MENU )
        {
            gameState = STATE_START_SCREEN;
        }
        else if ( signal == SIG_GAME_PAUSED )
        {
            //pause game if the game is currently running
            if ( gameState == STATE_RUNNING ) gameState = STATE_PAUSE_SCREEN;
        }
        
        else if ( signal == SIG_PLAYER_DEAD || signal == SIG_GEM_DESTROYED )
        {
            gameState = STATE_GAME_OVER_SCREEN;
        }
        else if ( signal == SIG_PLAYER_MOVE_N )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_N );
        }
        else if ( signal == SIG_PLAYER_MOVE_NE )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_NE );
        }
        else if ( signal == SIG_PLAYER_MOVE_E )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_E );
        }
        else if ( signal == SIG_PLAYER_MOVE_SE )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_SE );
        }
        else if ( signal == SIG_PLAYER_MOVE_S )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_S );
        }
        else if ( signal == SIG_PLAYER_MOVE_SW )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_SW );
        }
        else if ( signal == SIG_PLAYER_MOVE_W )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_W );
        }
        else if ( signal == SIG_PLAYER_MOVE_NW )
        {
            this->worldManager->movePlayer( TEXTURE_PLAYER_NW );
        }
        
        else if ( signal == SIG_MOUSE_LEFT_CLICK )
        {
            if ( gameState == STATE_RUNNING )
            {
                if ( gamePlayState == GAME_STATE_ATTACKING )
                {
                    attackState->handleMouseClick( sf::Mouse::getPosition( *mainWindow ).x, 
                                                   sf::Mouse::getPosition( *mainWindow ).y,
                                                   mainWindow->getSize().x / 2,
                                                   mainWindow->getSize().y / 2 );
                }
                else if ( gamePlayState == GAME_STATE_BUILDING )
                {
                    buildState->handleMouseClick( sf::Mouse::getPosition( *mainWindow ).x,
                                                  sf::Mouse::getPosition( *mainWindow ).y,
                                                  money );
                }
            }   
            else 
            {
                currentScreen->handleClick( sf::Mouse::getPosition( *mainWindow ).x,
                                            sf::Mouse::getPosition( *mainWindow ).y );
            }
        }
        
        else if ( signal == SIG_KEY_SPACE_PRESS )
        {
            attackState->fixWall();
        }
        
        else if ( signal == SIG_PICKUP_HEALTH )
        {
            worldManager->setPlayerHealth( 100 );
        }
        else if ( signal == SIG_PICKUP_AMMO )
        {
            attackState->addAmmo( 25 );
        }
        else if ( signal == SIG_PICKUP_REPAIRS )
        {
            attackState->addWallRepairs( 5 );
        }
        else if ( signal == SIG_BEGIN_ATTACK )
        {
            gamePlayState = GAME_STATE_ATTACKING;
            timeLeft = attackTimeS;
            this->gameClock.restart();
        }
        else if ( signal == SIG_GHOST_KILLED )
        {
            this->money += GHOST_KILL_REWARD; //give player some money for killing a ghost
        }
    }
}

void Game::run()
{
    sf::Clock fpsClock;
    fpsClock.restart();
    
    int fps = 0;
    while ( gameState != STATE_QUIT )
    {
        handleSignals();
        inputDriver->handleInput( this->mainWindow );
        
        switch ( gameState )
        {
            case STATE_START_SCREEN:
                currentScreen = startScreen;
                break;
            case STATE_PAUSE_SCREEN:
                currentScreen = pauseScreen;
                break;
            case STATE_GAME_OVER_SCREEN:
                currentScreen = gameOverScreen;
                break;
        }
        
        if ( gameState == STATE_RUNNING )
        {
            if ( gamePlayState == GAME_STATE_ATTACKING )
            {
                attackState->update( timeLeft );
                attackState->draw( videoDriver );
            }
            else if ( gamePlayState == GAME_STATE_BUILDING )
            {
                buildState->update( money, sf::Mouse::getPosition( *mainWindow ).x,
                                    sf::Mouse::getPosition( *mainWindow ).y,
                                    mainWindow->getSize().x, mainWindow->getSize().y );
                buildState->draw( videoDriver );
            }
        
            handleTimers();
        }
        else 
        {
            currentScreen->renderFrame( videoDriver );
        }
        
        if (  fpsClock.getElapsedTime().asSeconds() >= 1 )
        {
            printf( "fps: %i\n", fps );
            fps = 0;
            fpsClock.restart();
            
        }
        fps++;
        
    }
}

void Game::handleTimers()
{
    if ( gamePlayState == GAME_STATE_ATTACKING )
    {
        attackState->handleTimers();
    }
    
    if ( gameClock.getElapsedTime().asSeconds() >= 1 )
    {
        timeLeft--;
        gameClock.restart();
    }
    
    if ( gamePlayState == GAME_STATE_ATTACKING )
    {
        worldManager->setCreateMoreEnemies( true );
        if ( timeLeft <= 0 )
        {
            worldManager->setCreateMoreEnemies( false );
            if ( worldManager->getGhostCount() <= 0 )
            {
                gamePlayState = GAME_STATE_BUILDING;
                worldManager->clearBullets();
                worldManager->clearPickups();
                
                attackState->increaseLevel();
                this->gameClock.restart();
            }
        }
    }
    else if ( gamePlayState == GAME_STATE_BUILDING )
    {
        worldManager->setCreateMoreEnemies( false );
        
    }
}

std::string Game::getPathWithoutFileName( std::string path )
{
    int lastSlashIndex = 0;
    for ( int index = 0; index < path.size(); index++ )
    {
        //get the last slash index in the given path
        if ( path[index] == '/' || path[index] == '\\' ) {
            lastSlashIndex = index;
        }
    }
    
    return path.substr( 0, lastSlashIndex );
}

void Game::resetGame()
{
    this->worldManager->GenerateMap( programPathWithoutName + "/media/maps/simple.txt" );
    
    this->gamePlayState = GAME_STATE_BUILDING;
    this->timeLeft = attackTimeS;
    
}

