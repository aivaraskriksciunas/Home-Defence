#include "Game.h"

using namespace Engine;

Game::Game( char* programPath, char* title, int width, int height ) : 
    windowWidth( width ), windowHeight( height ) 
{
    
    this->mainWindow = new sf::RenderWindow( sf::VideoMode( this->windowWidth, this->windowHeight ),
                                             title,
                                             sf::Style::Default );
    
    this->mainWindow->setFramerateLimit( 80 );
    
    //get only the path to the file without the file name
    std::string programPathWithoutName = getPathWithoutFileName( programPath );
    
    //initialize drivers and managers
    this->videoDriver = new Engine::VideoDriver( this->mainWindow );
    this->textureManager = new Engine::TextureManager( programPathWithoutName );
    this->inputDriver = new Engine::InputDriver();
    this->worldManager = new World::WorldManager();
    this->worldManager->GenerateMap( programPathWithoutName + "/media/maps/simple.txt" );
    
    this->gameState = STATE_RUNNING;
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
        else if ( signal == SIG_MAP_SCROLL_UP )
        {
            this->worldManager->scrollMap( 0, 2 );
        }
        else if ( signal == SIG_MAP_SCROLL_DOWN )
        {
            this->worldManager->scrollMap( 0, -2 );
        }
        else if ( signal == SIG_MAP_SCROLL_RIGHT )
        {
            this->worldManager->scrollMap( -2, 0 );
        }
        else if ( signal == SIG_MAP_SCROLL_LEFT )
        {
            this->worldManager->scrollMap( 2, 0 );
        }
    }
}

void Game::renderFrame()
{
    if ( !this->texturesLoaded ) return;
    
    this->mainWindow->clear( sf::Color::Black );
    this->worldManager->renderMap( this->videoDriver );
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
        renderFrame();
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


