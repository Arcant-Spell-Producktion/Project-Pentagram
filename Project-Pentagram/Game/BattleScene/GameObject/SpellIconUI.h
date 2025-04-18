﻿#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"
#include <string>
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>
#include <Game/BattleScene/GameObject/SpellDetailUI.h>


class SpellIconUI: public Button
{
private:


    IGameObjectManager* m_ObjectManager;

    UIObject* m_IconObject;
    UIObject* m_IconHidden;
    UIObject* m_IconOverlay;
    UIObject* m_IconBorder;

    Element::Type m_CurrentElement = Element::NULLTYPE;

    float m_IconSize = 100.0f;
    float m_BorderSize = 114.0f;

    int m_BorderIndex = 0;
    int m_OverlayIndex = 0;

    bool m_isPentagramIcon = false;
    bool m_toggleOverlay = true;
    bool m_isPreview = false;

    bool m_IsBeingHover = false;

    int m_CurrentSpellIndex = -1;

    void HoldDetailBox();

    void ReleaseDetailBox();

public:
    CastSpellDetail* SpellDetail = nullptr;

    SpellIconUI(std::string objName,float scale = 100.0f);

    void SetOverlayToggle(bool flag);

    void SetDarken(bool flag);

    void SetTransparency(bool flag);

    void ToggleIsPentagramIcon(bool flag);

    void SetIcon(CastSpellDetail* spellDetail , bool doCast);

    void SetIsExtra(bool isExtra);

    void SetIsHidden(bool isHidden);

    void SetIsPreview(bool isPreview);

    void SetPosition(glm::vec3 position);

    void SetScale(glm::vec3 scale);

    void UpdateIcon();

    void SetActive(const bool& active) override;

    bool IsBeingHover() const;
};