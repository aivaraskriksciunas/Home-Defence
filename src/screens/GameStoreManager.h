#pragma once
#include <sstream>
#include "../ui/UIManager.h"
#include "../ui/UISelectButtonContainer.h"
#include "../ui/UISelectButton.h"
#include "../ui/UILabel.h"
#include "../engine/VideoDriver.h"
#include "../world/Tile.h"
#include "../characters/Defence.h"

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
    
    int getSelectedDefence();
    int getSelectedDefenceCost( int defenceType );
    
    void updateUI();
    
    
private:
    const int wallTypeCosts[World::WALL_TYPE_TOTAL] = { 5, 20 };
    const int defencesCosts[DEFENCE_TYPE_TOTAL] = { 0 };
    
    const int actionContainerWidth = 100, actionContainerHeight = 60;
    UI::UISelectButtonContainer* actionButtonContainer;
    UI::UISelectButton* actionBuildBtn;
    UI::UISelectButton* actionBuyDefencesBtn;
    
    const int buyWallsWidth = 200, buyWallsHeight = 60;
    UI::UISelectButtonContainer* buyWallsContainer;
    UI::UISelectButton* buyWall1Btn;
    UI::UISelectButton* buyWall2Btn;
    
    const int buyDefencesWidth = 100, buyDefencesHeight = 60;
    UI::UISelectButtonContainer* buyDefencesContainer;
    UI::UISelectButton* buyPlasmaGunBtn;
    
    UI::UIManager* uiManagerPtr;
};


