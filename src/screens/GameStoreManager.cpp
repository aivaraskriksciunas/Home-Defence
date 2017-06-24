#include "GameStoreManager.h"

GameStoreManager::GameStoreManager( UI::UIManager* uiManagerPtr, int windowWidth, int windowHeight )
{
    
    this->uiManagerPtr = uiManagerPtr;
    this->actionButtonContainer = new UI::UISelectButtonContainer( 0, windowHeight - actionContainerHeight,
                                                                  actionContainerWidth, actionContainerHeight,
                                                                  sf::Color( 150, 150, 150, 255 ) );
    this->actionBuildBtn = new UI::UISelectButton( 0, 0, actionContainerWidth, actionContainerHeight / 2,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Build",
                                                   SIG_NULL );
    this->actionBuyDefencesBtn = new UI::UISelectButton( 0, 30, actionContainerWidth, actionContainerHeight / 2,
                                                   sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200 ),
                                                   "Buy Defenses",
                                                   SIG_NULL );
    
    this->actionButtonContainer->addButton( actionBuildBtn );
    this->actionButtonContainer->addButton( actionBuyDefencesBtn );
    this->actionButtonContainer->setButtonsTextSize( 12 );
    
    this->buyWallsContainer = new UI::UISelectButtonContainer( windowWidth - buyWallsWidth, windowHeight - buyWallsHeight,
                                                               buyWallsWidth, buyWallsHeight,
                                                               sf::Color( 150, 150, 150, 255 ) );
    
    std::stringstream btnText;
    btnText.str( "" );
    btnText << "Wooden: " << wallTypeCosts[0];
    
    this->buyWall1Btn = new UI::UISelectButton( 0, 0, buyWallsWidth / 2, buyWallsHeight,
                                                sf::Color( 150, 150, 150, 255 ), sf::Color( 200, 200, 200, 255 ),
                                                btnText.str(),
                                                SIG_NULL );
    
    btnText.str( "" );
    btnText << "Brick: " << wallTypeCosts[1];
    
    this->buyWall2Btn = new UI::UISelectButton( 100, 0, buyWallsWidth / 2, buyWallsHeight,
                                                sf::Color( 150, 150, 150, 255 ), sf::Color( 180, 180, 180, 255 ),
                                                btnText.str(),
                                                SIG_NULL );
    
    buyWallsContainer->addButton( buyWall1Btn );
    buyWallsContainer->addButton( buyWall2Btn );
    
    this->buyWallsContainer->setVisible( false );
    
    
    this->buyDefencesContainer = new UI::UISelectButtonContainer( windowWidth - buyDefencesWidth, 
                                                                  windowHeight - buyDefencesHeight,
                                                                  buyDefencesWidth, buyDefencesHeight,
                                                                  sf::Color( 150, 150, 150, 255 ) );
    
    btnText.str( "" );
    btnText << "Plasma Gun: " << defencesCosts[0];
    this->buyPlasmaGunBtn = new UI::UISelectButton( 0, 0, buyDefencesWidth, buyDefencesHeight,
                                                    sf::Color( 150, 150, 150, 255 ), sf::Color( 180, 180, 180, 255 ),
                                                    btnText.str(),
                                                    SIG_NULL );
    
    this->buyDefencesContainer->addButton( buyPlasmaGunBtn );
    
    this->uiManagerPtr->AddElement( buyWallsContainer );
    this->uiManagerPtr->AddElement( actionButtonContainer );
    this->uiManagerPtr->AddElement( buyDefencesContainer );
}


int GameStoreManager::getBuildMode()
{
    if ( actionBuildBtn->isSelected() )
    {
        return MODE_BUILD_WALLS;
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
    
    if ( actionBuyDefencesBtn->isSelected() )
    {
        this->buyDefencesContainer->setVisible( true );
    }
    else 
    {
        this->buyDefencesContainer->setVisible( false );
    }
}

int GameStoreManager::getSelectedWall()
{
    if ( buyWall1Btn->isSelected() )
    {
        return World::WALL_TYPE_WOOD;
    }
    else if ( buyWall2Btn->isSelected() )
    {
        return World::WALL_TYPE_BRICK;
    }
    
    return World::WALL_TYPE_TOTAL;
}

int GameStoreManager::getSelectedWallCost( int wallType )
{
    if ( wallType >= World::WALL_TYPE_TOTAL || wallType < 0 ) return 0;
    
    return this->wallTypeCosts[wallType];
}

int GameStoreManager::getSelectedDefence()
{
    if ( buyPlasmaGunBtn->isSelected() )
    {
        return DEFENCE_TYPE_PLASMA_GUN;
    }
    return DEFENCE_TYPE_TOTAL;
}

int GameStoreManager::getSelectedDefenceCost( int defenceType )
{
    if ( defenceType >= DEFENCE_TYPE_PLASMA_GUN || defenceType < 0 ) return 0;
    
    return this->defencesCosts[defenceType];
}