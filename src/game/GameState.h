#pragma once

#include "../world/WorldManager.h"
#include "../engine/VideoDriver.h"

namespace GameStates {
class GameState {
public:
    
    virtual void update( int timeLeft ) = 0;
    virtual void draw( Engine::VideoDriver* videoDriver ) = 0;
    
    virtual void reset() = 0;

protected:
    World::WorldManager* worldManager;
    
};

}


