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
    
    this->mainViewport.setSize( width, height );
    this->uiViewport.setSize( width, height );
    this->uiViewport.setCenter( width / 2, height / 2 );
    
    //get only the path to the file without the file name
    std::string programPathWithoutName = getPathWithoutFileName( programPath );
    
    //initialize drivers and managers
    this->videoDriver = new Engine::VideoDriver( this->mainWindow );
    this->textureManager = new Engine::TextureManager( programPathWithoutName );
    this->inputDriver = new Engine::InputDriver();
    this->worldManager = new World::WorldManager();
    this->worldManager->GenerateMap( programPathWithoutName + "/media/maps/simple.txt" );
    this->uiManager = new UI::UIManager();
    
    this->gameState = STATE_RUNNING;
    this->ammo = 50;
    this->wallRepairs = 10;

    //initialize clocks 
    this->enemyMoveClock.restart();
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
        
        else if ( signal == SIG_KEY_SPACE_PRESS )
        {
            if ( wallRepairs > 0 )
            {
                if ( worldManager->fixWall() )
                    wallRepairs--;
            }
        }
    }
}

void Game::renderFrame()
{
    if ( !this->texturesLoaded ) return;
    
    this->mainWindow->clear( sf::Color::Black );
    
    
    this->mainWindow->setView( this->mainViewport );
    this->worldManager->renderMap( this->videoDriver );
    
    this->mainViewport.setCenter( worldManager->getPlayerX(), worldManager->getPlayerY() );
    
    
    this->mainWindow->setView( this->uiViewport );
    this->uiManager->drawUI( this->videoDriver );
    
    this->mainWindow->display();
    
}

void Game::run()
{
    sf::Clock fpsClock;
    fpsClock.restart();
    
    createGamePlayUI();
    
    int fps = 0;
    while ( gameState != STATE_QUIT )
    {
        handleSignals();
        updateUI();
        
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


void Game::createGamePlayUI()
{
    this->infoBox = new UI::UIBox( 0, 0, 100, 100 );
    
    this->healthLabel = new UI::UILabel( 30, 10, "0 ", sf::Color::White, FONT_SIMPLE, 17 );
    this->healthIcon = new UI::UIIcon( 5, 10, TEXTURE_ICON_HEART );
    this->ammoIcon = new UI::UIIcon( 5, 30, TEXTURE_ICON_BULLET );
    this->ammoLabel = new UI::UILabel( 30, 30, "0 ", sf::Color::White, FONT_SIMPLE, 17 );
    this->repairIcon = new UI::UIIcon( 5, 50, TEXTURE_ICON_HAMMER );
    this->repairLabel = new UI::UILabel( 30, 50, "0", sf::Color::White, FONT_SIMPLE, 17 );
    
    this->infoBox->addElement( healthLabel );
    this->infoBox->addElement( healthIcon );
    this->infoBox->addElement( ammoLabel );
    this->infoBox->addElement( ammoIcon );
    this->infoBox->addElement( repairIcon );
    this->infoBox->addElement( repairLabel );
    
    uiManager->AddElement( infoBox );
}

void Game::updateUI()
{
    std::stringstream text( "" );
    text << ammo;
    this->ammoLabel->setText( text.str() );
    
    text.str( "" );
    text << wallRepairs;
    this->repairLabel->setText( text.str() );
    
    text.str( "" );
    text << worldManager->getPlayerHealth();
    this->healthLabel->setText( text.str() );
    
}