#pragma once 

#include <sstream>

#include "Screen.h"
#include "../ui/UIBox.h"
#include "../ui/UILabel.h"
#include "../ui/UIIcon.h"
#include "../ui/UIProgressBar.h"
#include "../ui/UIButton.h"
#include "../world/WorldManager.h"

namespace Screens {
    
class GameBuildScreen : public Screen {
public:
    GameBuildScreen( int windowWidth, int windowHeight );
    
    void renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager );
    
    void updateUI( int timeLeft, int money );
    
private:
    //all ui elements
    UI::UIBox* infoBox;
    UI::UIBox* timeBox;
    
    UI::UILabel* timeLabel;
    UI::UILabel* moneyLabel;
    
    UI::UIButton* startAttackButton;
    
    sf::View mainViewport;
    sf::View uiViewport;
};

}



