#include "Game.h"

using namespace Engine;

Game::Game( char* programPath, char* title, int width, int height ) : 
    windowWidth( width ), windowHeight( height ) 
{
    
    this->mainWindow = new sf::RenderWindow( sf::VideoMode( this->windowWidth, this->windowHeight ),
                                             title,
                                             sf::Style::Default );
    
    this->mainWindow->setFramerateLimit( 80 );
    
    this->mainViewport.setSize( width, height );
    this->mainWindow->setView( this->mainViewport );
    
    //get only the path to the file without the file name
    std::string programPathWithoutName = getPathWithoutFileName( programPath );
    
    //initialize drivers and managers
    this->videoDriver = new Engine::VideoDriver( this->mainWindow );
    this->textureManager = new Engine::TextureManager( programPathWithoutName );
    this->inputDriver = new Engine::InputDriver();
    this->worldManager = new World::WorldManager();
    this->worldManager->GenerateMap( programPathWithoutName + "/media/maps/simple.txt" );
    
    this->gameState = STATE_RUNNING;
    
    //initialize clocks 
    this->enemyMoveClock.restart();
}

void Game::handleSignals()
{
    int signal = 0;
    while ( SignalManager::pollSignal( signal ) )
    {
        if ( signal == SIG_QUIT || signal == SIG_ERROR )
        {
            gameState = STATE_QUIT;
        }
        else if ( signal == SIG_TEXTURE_LOAD_ERROR )
        {
            gameState = STATE_QUIT;
            this->texturesLoaded = false;
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
        
        if ( signal == SIG_MOUSE_LEFT_CLICK )
        {
            int mouseX = sf::Mouse::getPosition( (*mainWindow) ).x;
            int mouseY = sf::Mouse::getPosition( (*mainWindow) ).y;
            
            int screenMiddleX = mainWindow->getSize().x / 2;
            int screenMiddleY = mainWindow->getSize().y / 2;
            float direction = std::atan2( mouseY - screenMiddleY,
                                        mouseX - screenMiddleX );
            
            direction *= 180 / M_PI; //convert to degrees
            
            this->worldManager->shoot( direction );
        }
    }
}

void Game::renderFrame()
{
    if ( !this->texturesLoaded ) return;
    
    this->mainWindow->clear( sf::Color::Black );
    this->worldManager->renderMap( this->videoDriver );
    
    this->mainViewport.setCenter( worldManager->getPlayerX(), worldManager->getPlayerY() );
    this->mainWindow->setView( this->mainViewport );
    this->mainWindow->display();
    
}

void Game::run()
{
    sf::Clock fpsClock;
    fpsClock.restart();
    int fps = 0;
    while ( gameState != STATE_QUIT )
    {
        handleSignals();
        
        if (  fpsClock.getElapsedTime().asSeconds() >= 1 )
        {
            printf( "fps: %i\n", fps );
            fps = 0;
            fpsClock.restart();
            
        }
        fps++;
        
        inputDriver->handleInput( this->mainWindow );
        
        handleTimers();
        
        renderFrame();
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
