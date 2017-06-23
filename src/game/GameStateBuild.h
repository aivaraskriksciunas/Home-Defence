#pragma once
#include "../screens/GameBuildScreen.h"

namespace GameStates {
class GameStateBuild {
public:
    GameStateBuild( World::WorldManager* worldManager, int windowWidth, int windowHeight );
    
    void update( int money, int mouseX, int mouseY, int windowWidth, int windowHeight );
    void draw( Engine::VideoDriver* videoDriver );
    
    void reset();
    
    void handleMouseClick( int mouseX, int mouseY, int& money );
    
private:
    World::WorldManager* worldManager;
    Screens::GameBuildScreen* screen;
};

}

