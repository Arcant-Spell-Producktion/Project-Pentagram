﻿#include "MapNode.h"
#include <string>

const std::string MapNodeSpritePath = "Sprites/Map/map_pins.png";

MapNode::MapNode(Element::Type element): Button(element + "mapNode")
{
    m_Element = element;
    this->SetTexture(MapNodeSpritePath);
    this->SetIsSlicing(false);

    this->SetSpriteByIndex(0,(int)element);

    this->scale = {80.0f, 120.0f, 1.0f};
}
