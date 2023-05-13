#pragma once
#include <array>
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"

class ClickableSpellIconUI : public SpellIconUI
{
public:
    Event<int> OnSpellClick;

    ClickableSpellIconUI(const std::string& objName)
        : SpellIconUI(objName , 75.0f)
    {
        this->onClick = [this](Button* button)
        {
            OnSpellClick.Invoke(this->SpellDetail->GetIndex());
        };
    }
};

class PentagramSpellSelector : public UIObject
{
private:
    Element::Type m_CurrentElement = Element::Earth;
    bool m_IsHighlightColumn = true;

    int m_Circle = 1;
    int m_Complex = 1;
    int m_Will = 1;
    int m_Effect = 1;

    std::array<std::array<ClickableSpellIconUI*,3>,3> m_SpellIcons;

    void UpdateIconDetail();

    void ClickIcon(int index);
public:
    Event<PentagramData_T> OnSpellClick;

    PentagramSpellSelector();

    void SetElement(Element::Type element);

    void UpdateSpellIcons(PentagramEvent e);

    void Reset();

};
