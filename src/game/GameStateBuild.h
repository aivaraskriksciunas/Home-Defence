#pragma once
#include "../screens/GameBuildScreen.h"
#include "GameState.h"

namespace GameStates {
class GameStateBuild : public GameState {
public:
    GameStateBuild( World::WorldManager* worldManager, int windowWidth, int windowHeight );
    
    void update( int timeLeft );
    void draw( Engine::VideoDriver* videoDriver );
    
    void reset();
    
private:
    Screens::GameBuildScreen* screen;
};

}

