#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"
#include <string>
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

enum class IconType
{
    Normal,
    Extra,
};

class SpellIconUI: public Button
{
private:

    IconType m_Type = IconType::Normal;

    IGameObjectManager* m_ObjectManager;

    UIObject* m_IconObject;
    UIObject* m_IconBorder;

    Element::Type m_CurrentElement = Element::NULLTYPE;
    int m_CurrentSpellIndex = -1;
public:
    CastSpellDetail* SpellDetail = nullptr;

    SpellIconUI(std::string objName);

    void SetIcon(CastSpellDetail* spellDetail);

    void SetIconType(IconType type) { m_Type = type; };

    void SetPosition(glm::vec3 position);

    void SetTransparency(bool flag);

    void UpdateIcon();

    void UpdateDetail();
};