#include "UIManager.h"

using namespace UI;

UIManager::UIManager( )
{
    
}

void UIManager::AddElement( UIElement* element )
{
    this->uiElements.push_back( element );
}

void UIManager::drawUI( Engine::VideoDriver* videoDriver )
{
    for ( int uiIndex = 0; uiIndex < uiElements.size(); uiIndex++ )
    {
        uiElements[uiIndex]->draw( videoDriver );
    }
}