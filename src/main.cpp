#include "Game.h"


int main( int argc, char* argv[] )
{
    Game game( argv[0], "Subway Rider", 1024, 700 );
    game.run();
    
    return 0;
}

