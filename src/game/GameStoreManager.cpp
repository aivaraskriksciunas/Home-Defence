#include "GameStoreManager.h"

GameStoreManager::GameStoreManager( UI::UIManager* uiManagerPtr, int windowWidth, int windowHeight )
{
    
    this->uiManagerPtr = uiManagerPtr;
    this->actionButtonContainer = new UI::UISelectButtonContainer( 0, windowHeight - actionContainerHeight,
                                                                  actionContainerWidth, actionContainerHeight,
                                                                  sf::Color( 150, 150, 150, 255 ) );
    this->actionBuildBtn = new UI::UISelectButton( 0, 0, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Build",
                                                   SIG_NULL );
    this->actionRebuildWallsBtn = new UI::UISelectButton( 0, 30, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Rebuild Walls",
                                                   SIG_REBUILD_WALLS );
    this->actionBuyDefencesBtn = new UI::UISelectButton( 0, 60, actionContainerWidth, actionContainerHeight / 3,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Buy Defenses",
                                                   SIG_NULL );
    
    this->actionButtonContainer->addButton( actionBuildBtn );
    this->actionButtonContainer->addButton( actionRebuildWallsBtn );
    this->actionButtonContainer->addButton( actionBuyDefencesBtn );
    this->actionButtonContainer->setButtonsTextSize( 12 );
    
    this->buyWallsContainer = new UI::UISelectButtonContainer( windowWidth - buyWallsWidth, windowHeight - buyWallsHeight,
                                                               buyWallsWidth, buyWallsHeight,
                                                               sf::Color( 150, 150, 150, 255 ) );
    
    std::stringstream btnText;
    btnText.str( "" );
    btnText << "Wooden: " << WALL_1_COST;
    
    this->buyWall1Btn = new UI::UISelectButton( 0, 0, buyWallsWidth / 2, buyWallsHeight,
                                                sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200, 255 ),
                                                btnText.str(),
                                                SIG_NULL );
    
    btnText.str( "" );
    btnText << "Brick: " << WALL_2_COST;
    
    this->buyWall2Btn = new UI::UISelectButton( 100, 0, buyWallsWidth / 2, buyWallsHeight,
                                                sf::Color( 150, 150, 150, 255 ), sf::Color( 180, 180, 180, 255 ),
                                                btnText.str(),
                                                SIG_NULL );
    
    buyWallsContainer->addButton( buyWall1Btn );
    buyWallsContainer->addButton( buyWall2Btn );
    
    this->buyWallsContainer->setVisible( false );
    
    this->uiManagerPtr->AddElement( buyWallsContainer );
    this->uiManagerPtr->AddElement( actionButtonContainer );
}


int GameStoreManager::getBuildMode()
{
    if ( actionBuildBtn->isSelected() )
    {
        return MODE_BUILD_WALLS;
    }
    else if ( actionRebuildWallsBtn->isSelected() )
    {
        return MODE_BUILD_NONE;
    }
    else if ( actionBuyDefencesBtn->isSelected() )
    {
        return MODE_BUILD_DEFENCES;
    }
}

void GameStoreManager::updateUI()
{
    if ( actionBuildBtn->isSelected() )
    {
        this->buyWallsContainer->setVisible( true );
    }
    else 
    {
        this->buyWallsContainer->setVisible( false );
    }
}