#include "UIIcon.h"

using namespace UI;

UIIcon::UIIcon( int posx, int posy, int textureID )
{
    this->posx = posx;
    this->posy = posy;
    this->textureID = textureID;
}

UIIcon::UIIcon() {};


void UIIcon::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawTexture( Engine::TextureManager::getTexture( textureID ),
                              this->posx, this->posy );
}
