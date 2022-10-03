#pragma once
#include "Engine/GameScene.h"
#include "Game/Spells/Element.h"
#include <string>
class SpellIconUI
{
private:
    GameScene* m_Scene;

    GameObject* m_IconObject;
public:
    SpellIconUI(std::string objName);

    void SetIcon(Element::Type element,int spellIndex);

    void SetPosition(glm::vec3 position);
};