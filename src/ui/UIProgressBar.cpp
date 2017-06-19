#include "UIProgressBar.h"

using namespace UI;

UIProgressBar::UIProgressBar( int posx, int posy, int width, int height, int maxValue, sf::Color bgColor )
{
    this->posx = posx;
    this->posy = posy;
    this->width = width;
    this->height = height;
    this->maxValue = maxValue;
    this->bgColor = bgColor;
}

void UIProgressBar::draw( Engine::VideoDriver* videoDriver )
{
    videoDriver->drawRectangle( this->bgColor,
                                posx, posy,
                                calculateBarLength(),
                                height );
}

void UIProgressBar::setMaxValue( int value )
{
    this->maxValue = value;
}

void UIProgressBar::setValue( int value )
{
    this->value = value;
}

int UIProgressBar::calculateBarLength()
{
    //get the progress bar percentage
    float valuePercent = value / maxValue;
    
    return this->width * valuePercent;
    
}