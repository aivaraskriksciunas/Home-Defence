#pragma once
#include "GameState.h"
#include "../screens/GameAttackScreen.h"

#define STARTING_AMMO 1000000
#define STARTING_WALL_REPAIRS 10

namespace GameStates {
class GameStateAttack : public GameState {
public:
    GameStateAttack( World::WorldManager* worldManagerPtr, int windowWidth, int windowHeight );
    
    void update( int timeLeft );
    void draw( Engine::VideoDriver* videoDriver );
    
    void reset();
    
    void handleMouseClick( int mouseX, int mouseY,
                           int windowMiddleX, int windowMiddleY );
    
    void fixWall();
    void addAmmo( int amount );
    void addWallRepairs( int amount );
    
    void handleTimers();
    
    void increaseLevel();
     
private:
    Screens::GameAttackScreen* screen;
    
    //game stats
    int ammo;
    int wallRepairs;
    
    int gameLevel = 1;
    
    const int enemyMoveIntervalMs = 30;
    const int gemDamageIntervalMs = 300;
    
    sf::Clock enemyMoveClock;
    sf::Clock gemDamageClock;
};

}

