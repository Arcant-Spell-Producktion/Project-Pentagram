#pragma once
#include "Engine/GameScene.h"
#include "Game/Spells/Element.h"
#include <string>
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellIconUI: public Button
{
private:
    GameScene* m_Scene;

    UIObject* m_IconObject;
    UIObject* m_IconBorder;

    Element::Type m_CurrentElement = Element::NULLTYPE;
    int m_CurrentSpellIndex = -1;
public:
    CastSpellDetail* SpellDetail = nullptr;

    SpellIconUI(std::string objName);

    void SetIcon(CastSpellDetail* spellDetail);

    void SetPosition(glm::vec3 position);

    void SetTransparency(bool flag);

    void UpdateIcon();

    void UpdateDetail();
};