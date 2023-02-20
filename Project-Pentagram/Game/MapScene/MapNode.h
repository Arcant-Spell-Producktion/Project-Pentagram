#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"

class MapNode : public Button
{
private:
    Element::Type m_Element;
public:
    Event<Element::Type> OnNodeClick;

    MapNode(Element::Type element);
};