#pragma once
#include "../screens/GameBuildScreen.h"

namespace GameStates {
class GameStateBuild {
public:
    GameStateBuild( World::WorldManager* worldManager, int windowWidth, int windowHeight );
    
    void update( int money );
    void draw( Engine::VideoDriver* videoDriver );
    
    void reset();
    
    void handleMouseClick( int mouseX, int mouseY );
    
private:
    World::WorldManager* worldManager;
    Screens::GameBuildScreen* screen;
};

}

