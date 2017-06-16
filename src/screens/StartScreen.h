#pragma once 

#include "Screen.h"
#include "../ui/UIButton.h"

namespace Screens {
    
class StartScreen : public Screen {
public:
    StartScreen();
    
private:
    UI::UILabel title;
    UI::UIButton startButton;
    UI::UIButton quitButton;
    
};

}

