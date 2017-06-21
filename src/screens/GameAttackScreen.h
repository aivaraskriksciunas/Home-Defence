#pragma once 

#include <sstream>

#include "Screen.h"
#include "../ui/UIBox.h"
#include "../ui/UILabel.h"
#include "../ui/UIIcon.h"
#include "../ui/UIProgressBar.h"
#include "../world/WorldManager.h"

namespace Screens {
    
class GameAttackScreen : public Screen {
public:
    GameAttackScreen( int windowWidth, int windowHeight );
    
    void renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager);
    
    void updateUI( int ammo, int wallRepairs, int playerHealth, int gemHealth, int timeLeft );
    
private:
    const int maxProgressBarLength = 60;
    
    //all ui elements
    UI::UIBox* infoBox;
    UI::UIBox* timeBox;
    
    UI::UIProgressBar* healthLabel;
    UI::UILabel* ammoLabel;
    UI::UILabel* repairLabel;
    UI::UIProgressBar* gemLabel;
    UI::UIIcon* repairIcon;
    UI::UIIcon* healthIcon;
    UI::UIIcon* ammoIcon;
    UI::UIIcon* gemIcon;
    
    UI::UILabel* timeLabel;
    
    sf::View mainViewport;
    sf::View uiViewport;
};

}

