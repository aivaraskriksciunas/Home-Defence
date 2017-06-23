#pragma once
#include <sstream>
#include "../ui/UIManager.h"
#include "../ui/UISelectButtonContainer.h"
#include "../ui/UISelectButton.h"
#include "../ui/UILabel.h"
#include "../engine/VideoDriver.h"
#include "../world/Tile.h"

enum BuildModes {
    MODE_BUILD_WALLS,
    MODE_BUILD_DEFENCES,
    MODE_BUILD_NONE
};

class GameStoreManager {
public:
    GameStoreManager( UI::UIManager* uiManagerPtr, int windowWidth, int windowHeight );
    
    int getBuildMode();
    int getSelectedWall();
    int getSelectedWallCost( int wallType );
    
    void updateUI();
    
    
private:
    const int wallTypeCosts[World::WALL_TYPE_TOTAL] = { 5, 20 };
    
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


