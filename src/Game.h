#pragma once
#include <string>

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
#include "screens/PauseScreen.h"
#include "screens/GameOverScreen.h"

#include "game/GameStateAttack.h"
#include "game/GameStateBuild.h"

#define ATTACK_TIME_INCREASE 10

class Game
{
public:
    Game( char* programPath, char* title, int width, int height );
    void run();
    
private:
    void handleSignals();
    
    void resetGame();
    
    const int windowWidth, windowHeight;
    sf::RenderWindow* mainWindow;
    
    //screens
    Screens::StartScreen* startScreen;
    Screens::PauseScreen* pauseScreen;
    Screens::GameOverScreen* gameOverScreen;
    Screens::Screen* currentScreen;
    
    Engine::TextureManager* textureManager;
    Engine::VideoDriver* videoDriver;
    Engine::InputDriver* inputDriver;
    World::WorldManager* worldManager;
    
    //mid-game states
    GameStates::GameStateAttack* attackState;
    GameStates::GameStateBuild* buildState;
    
    enum ProgramStates {
        STATE_START_SCREEN, 
        STATE_PAUSE_SCREEN,
        STATE_GAME_OVER_SCREEN,
        STATE_RUNNING,
        STATE_QUIT
    };
    
    enum GamePlayStates {
        GAME_STATE_ATTACKING,
        GAME_STATE_BUILDING
    };
    
    int gameState;
    int gamePlayState;
    
    bool texturesLoaded = true;
    
    //game clocks
    //max amount of time player has to upgrade their building
    const int gameBuildTimeS = 1;
    //time the player will be attacked by ghosts
    int attackTimeS = 60 * 1;
    int timeLeft = 0;
    //clock to measure attack and build game mode
    sf::Clock gameClock;
    
    //this function strips away the file name from full argv path
    std::string getPathWithoutFileName( std::string path );
    
    std::string programPathWithoutName;
    
    //this checks all timers
    void handleTimers();
    
};

