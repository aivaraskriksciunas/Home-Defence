#pragma once
#include <sstream>
#include "../ui/UIManager.h"
#include "../ui/UISelectButtonContainer.h"
#include "../ui/UISelectButton.h"
#include "../ui/UILabel.h"
#include "../engine/VideoDriver.h"

#define WALL_1_COST 5
#define WALL_2_COST 20

enum BuildModes {
    MODE_BUILD_WALLS,
    MODE_BUILD_DEFENCES,
    MODE_BUILD_NONE
};

enum WallBuildModes {
    WALL_BUILD_1,
    WALL_BUILD_2,
    WALL_BUILD_NONE
};

class GameStoreManager {
public:
    GameStoreManager( UI::UIManager* uiManagerPtr, int windowWidth, int windowHeight );
    
    int getBuildMode();
    
    void updateUI();
    
private:
    
    const int actionContainerWidth = 100, actionContainerHeight = 90;
    UI::UISelectButtonContainer* actionButtonContainer;
    UI::UISelectButton* actionBuildBtn;
    UI::UISelectButton* actionRebuildWallsBtn;
    UI::UISelectButton* actionBuyDefencesBtn;
    
    const int buyWallsWidth = 200, buyWallsHeight = 60;
    UI::UISelectButtonContainer* buyWallsContainer;
    UI::UISelectButton* buyWall1Btn;
    UI::UISelectButton* buyWall2Btn;
    
    UI::UIManager* uiManagerPtr;
};


