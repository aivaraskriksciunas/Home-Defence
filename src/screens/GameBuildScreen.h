#pragma once 

#include <sstream>

#include "Screen.h"
#include "../ui/UIBox.h"
#include "../ui/UILabel.h"
#include "../ui/UIIcon.h"
#include "../ui/UIProgressBar.h"
#include "../ui/UIButton.h"
#include "../ui/UISelectButton.h"
#include "../ui/UISelectButtonContainer.h"
#include "../world/WorldManager.h"

namespace Screens {
    
class GameBuildScreen : public Screen {
public:
    GameBuildScreen( int windowWidth, int windowHeight );
    
    void renderFrame( Engine::VideoDriver* videoDriver, World::WorldManager* worldManager );
    
    void updateUI( int money );
    
private:
    //all ui elements
    UI::UIBox* infoBox;
    UI::UILabel* moneyLabel;
    
    UI::UIButton* startAttackButton;
    
    const int actionContainerWidth = 100, actionContainerHeight = 90;
    UI::UISelectButtonContainer* actionButtonContainer;
    UI::UISelectButton* actionBuildBtn;
    UI::UISelectButton* actionRebuildWallsBtn;
    UI::UISelectButton* actionBuyDefensesBtn;
    
    sf::View mainViewport;
    sf::View uiViewport;
};

}



