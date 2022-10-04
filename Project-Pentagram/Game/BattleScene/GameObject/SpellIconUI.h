#pragma once
#include "Engine/GameScene.h"
#include "Game/Spells/Element.h"
#include <string>
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellIconUI: public Button
{
private:
    GameScene* m_Scene;

    GameObject* m_IconObject;

    Element::Type m_CurrentElement = Element::NULLTYPE;
    int m_CurrentSpellIndex = -1;
    CastSpellDetail* m_SpellDetail = nullptr;
public:
    SpellIconUI(std::string objName);

    void SetIcon(Element::Type element,int spellIndex);

    void SetPosition(glm::vec3 position);

    void SetDetail(CastSpellDetail* spellDetail);

    void UpdateIcon();

    void UpdateDetail();
};