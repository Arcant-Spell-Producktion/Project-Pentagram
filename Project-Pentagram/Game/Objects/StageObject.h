#pragma once
#include "Engine/GameScene.h"
#include "Game/Spells/Element.h"

class StageObject :public GameObject
{
private:
    GameScene* m_ObjectManager;
    Element::Type m_Element;

    GameObject* m_Background;
    GameObject* m_Floor;

public:
    StageObject(Element::Type element);
};