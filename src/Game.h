#pragma once
#include <string>

#include <cstdio>

#include "SFML/Graphics.hpp"

#include "engine/VideoDriver.h"
#include "engine/TextureManager.h"
#include "engine/InputDriver.h"
#include "world/WorldManager.h"

class Game
{
public:
    Game( char* programPath, char* title, int width, int height );
    void run();
    
private:
    void renderFrame();
    void handleSignals();
    
    const int windowWidth, windowHeight;
    sf::RenderWindow* mainWindow;
    sf::View mainViewport;
    
    Engine::TextureManager* textureManager;
    Engine::VideoDriver* videoDriver;
    Engine::InputDriver* inputDriver;
    World::WorldManager* worldManager;
    
    enum GameStates {
        STATE_SPLASH, 
        STATE_RUNNING,
        STATE_QUIT
    };
    
    int gameState;
    
    bool texturesLoaded = true;
    
    //this function strips away the file name from full argv path
    std::string getPathWithoutFileName( std::string path );
    
};

