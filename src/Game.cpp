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
            if ( gameState == STATE_START_SCREEN )
            {
                startScreen.handleClick( sf::Mouse::getPosition( *mainWindow ).x,
                                         sf::Mouse::getPosition( *mainWindow ).y );
            }
            else if ( gameState == STATE_RUNNING )
            {
                if ( ammo > 0 )
                {
                    int mouseX = sf::Mouse::getPosition( (*mainWindow) ).x;
                    int mouseY = sf::Mouse::getPosition( (*mainWindow) ).y;

                    int screenMiddleX = mainWindow->getSize().x / 2;
                    int screenMiddleY = mainWindow->getSize().y / 2;
                    float direction = std::atan2( mouseY - screenMiddleY,
                                                mouseX - screenMiddleX );

                    direction *= 180 / M_PI; //convert to degrees

                    this->worldManager->shoot( direction );

                    ammo--;
                }
            }   
        }
        
        else if ( signal == SIG_KEY_SPACE_PRESS )
        {
            if ( wallRepairs > 0 )
            {
                if ( worldManager->fixWall() )
                    wallRepairs--;
            }
        }
        
        else if ( signal == SIG_PICKUP_HEALTH )
        {
            worldManager->setPlayerHealth( 100 );
        }
        else if ( signal == SIG_PICKUP_AMMO )
        {
            ammo += 25;
        }
        else if ( signal == SIG_PICKUP_REPAIRS )
        {
            wallRepairs += 5;
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
        
        if ( gameState == STATE_RUNNING )
        {
            gameScreen->updateUI( this->ammo, this->wallRepairs, this->worldManager->getPlayerHealth() );
        
            handleTimers();

            gameScreen->renderFrame( videoDriver, worldManager );
        }
        else if ( gameState == STATE_START_SCREEN )
        {
            startScreen.renderFrame( videoDriver );
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
    if ( enemyMoveClock.getElapsedTime().asMilliseconds() >= enemyMoveIntervalMs )
    {
        worldManager->updateEnemies();
        worldManager->updateBullets();
        enemyMoveClock.restart();
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
    
    this->ammo = 50;
    this->wallRepairs = 10;
    
    //initialize clocks 
    this->enemyMoveClock.restart();
    
    //reset game screen
    this->gameScreen = new Screens::GameScreen( windowWidth, windowHeight );
}