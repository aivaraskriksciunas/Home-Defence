#pragma once
#include <queue>

enum Signals {
    SIG_NULL,
    SIG_ERROR,
    SIG_TEXTURE_LOAD_ERROR,
    SIG_MAP_LOAD_ERROR,
    SIG_MAP_SCROLL_UP,
    SIG_MAP_SCROLL_DOWN,
    SIG_MAP_SCROLL_LEFT,
    SIG_MAP_SCROLL_RIGHT,
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


