#pragma once
#include "Engine/GameScene.h"
#include "Game/Spells/Element.h"

class StageObject :public GameObject
{
private:

    Element::Type m_Element;

    GameObject* m_FadeScreen;

    GameObject* m_Background;
    GameObject* m_Floor;

    bool m_FadeIn = false;
    float m_FadeSpeed = 0.5f;
    float m_FadeTimer = 0.0f;

public:
    StageObject(Element::Type element);

    void SetElement(Element::Type element);

    void FadeToBlack();

    void OnUpdate(const float& dt) override;
};