#include "SignalManager.h"

using namespace Engine;

std::queue<int> SignalManager::signals;

SignalManager::SignalManager() {}

void SignalManager::sendSignal( int signal )
{
    signals.push( signal );
}

bool SignalManager::pollSignal( int& signal )
{
    if ( signals.size() > 0 )
    {
        //get the first signal
        signal = signals.front();
        //remove the first signal
        signals.pop();
        
        return true;
    }
    
    //no signals
    return false;
}