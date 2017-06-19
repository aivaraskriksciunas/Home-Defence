#pragma once 

#include <sstream>

#include "Screen.h"
#include "../ui/UIBox.h"
#include "../ui/UILabel.h"
#include "../ui/UIIcon.h"
#include "../world/WorldManager.h"

namespace Screens {
    
class GameScreen : public Screen {
public:
    GameScreen( int windowWidth, int windowHeight );
    
    void renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager);
    
    void updateUI( int ammo, int wallRepairs, int playerHealth, int gemHealth );
    
private:
    //all ui elements
    UI::UIBox* infoBox;
    UI::UILabel* healthLabel;
    UI::UILabel* ammoLabel;
    UI::UILabel* repairLabel;
    UI::UILabel* gemLabel;
    UI::UIIcon* repairIcon;
    UI::UIIcon* healthIcon;
    UI::UIIcon* ammoIcon;
    UI::UIIcon* gemIcon;
    
    sf::View mainViewport;
    sf::View uiViewport;
};

}

