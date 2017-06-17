#pragma once
#include <queue>

enum Signals {
    SIG_NULL,
    SIG_ERROR,
    SIG_TEXTURE_LOAD_ERROR,
    SIG_RESOURCE_LOAD_ERROR,
    
    SIG_GAME_RESTART,
    SIG_GAME_RESUME,
    SIG_GAME_STATE_MENU,
    SIG_GAME_PAUSED,
    
    SIG_PLAYER_DEAD,
    SIG_PLAYER_MOVE_N,
    SIG_PLAYER_MOVE_NE,
    SIG_PLAYER_MOVE_E,
    SIG_PLAYER_MOVE_SE,
    SIG_PLAYER_MOVE_S,
    SIG_PLAYER_MOVE_SW,
    SIG_PLAYER_MOVE_W,
    SIG_PLAYER_MOVE_NW,
    
    SIG_MOUSE_LEFT_CLICK,
    SIG_KEY_SPACE_PRESS,
    
    SIG_PICKUP_AMMO,
    SIG_PICKUP_HEALTH,
    SIG_PICKUP_REPAIRS,
    
    SIG_QUIT
};

namespace Engine {
    
class SignalManager
{
public:
    static void sendSignal( int signal );
    static bool pollSignal( int& signal );
    
private:
    static std::queue<int> signals;
    
    SignalManager();
};
}


