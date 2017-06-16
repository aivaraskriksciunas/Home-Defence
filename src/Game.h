#pragma once
#include <string>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "engine/VideoDriver.h"
#include "engine/TextureManager.h"
#include "engine/InputDriver.h"
#include "world/WorldManager.h"

#include "ui/UIManager.h"
#include "ui/UIBox.h"
#include "ui/UILabel.h"
#include "ui/UIIcon.h"

#include "screens/StartScreen.h"

class Game
{
public:
    Game( char* programPath, char* title, int width, int height );
    void run();
    
private:
    void renderFrame();
    void handleSignals();
    
    void resetGame();
    
    const int windowWidth, windowHeight;
    sf::RenderWindow* mainWindow;
    sf::View mainViewport;
    sf::View uiViewport;
    
    //screens
    Screens::StartScreen startScreen;
    
    Engine::TextureManager* textureManager;
    Engine::VideoDriver* videoDriver;
    Engine::InputDriver* inputDriver;
    World::WorldManager* worldManager;
    UI::UIManager* uiManager;
    
    enum GameStates {
        STATE_START_SCREEN, 
        STATE_RUNNING,
        STATE_QUIT
    };
    
    int gameState;
    
    //game stats
    int ammo;
    int wallRepairs;
    
    bool texturesLoaded = true;
    
    //game clocks
    const int enemyMoveIntervalMs = 30;
    sf::Clock enemyMoveClock;
    
    //this function strips away the file name from full argv path
    std::string getPathWithoutFileName( std::string path );
    
    std::string programPathWithoutName;
    
    //this checks all timers
    void handleTimers();
    
    //all ui elements
    UI::UIBox* infoBox;
    UI::UILabel* healthLabel;
    UI::UILabel* ammoLabel;
    UI::UILabel* repairLabel;
    UI::UIIcon* repairIcon;
    UI::UIIcon* healthIcon;
    UI::UIIcon* ammoIcon;
    
    //ui functions
    void createGamePlayUI();
    void updateUI();
    
};

