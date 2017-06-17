#pragma once

#include "Screen.h"
#include "../ui/UIButton.h"

namespace Screens {
    
class GameOverScreen : public Screen {
public:
    GameOverScreen( int windowWidth, int windowHeight );
    
private:
    UI::UILabel title;
    UI::UIButton restartButton;
    UI::UIButton menuButton;
    UI::UIButton quitButton;
    
    const int buttonWidth = 250, buttonHeight = 50;
};

}

