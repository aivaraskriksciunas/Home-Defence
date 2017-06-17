#pragma once

#include "Screen.h"
#include "../ui/UIButton.h"

namespace Screens {
    
class PauseScreen : public Screen {
public:
    PauseScreen( int windowWidth, int windowHeight );
    
private:
    UI::UILabel title;
    UI::UIButton startButton;
    UI::UIButton restartButton;
    UI::UIButton quitButton;
    
    const int buttonWidth = 250, buttonHeight = 50;
};

}

