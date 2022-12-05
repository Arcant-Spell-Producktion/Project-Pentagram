#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"
#include <string>
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellIconUI: public Button
{
private:
    IGameObjectManager* m_ObjectManager;

    UIObject* m_IconObject;
    UIObject* m_IconOverlay;
    UIObject* m_IconBorder;

    Element::Type m_CurrentElement = Element::NULLTYPE;

    float m_IconSize = 100.0f;
    float m_BorderSize = 114.0f;

    int m_BorderIndex = 0;
    int m_OverlayIndex = 0;

    bool m_isPreview = false;
    int m_CurrentSpellIndex = -1;

    void SetTransparency(bool flag);

public:
    CastSpellDetail* SpellDetail = nullptr;

    SpellIconUI(std::string objName,float scale = 100.0f);

    void SetIcon(CastSpellDetail* spellDetail , bool doCast);

    void SetIsExtra(bool isExtra);

    void SetIsPreview(bool isPreview);

    void SetPosition(glm::vec3 position);

    void UpdateIcon();

    void UpdateDetail();
};