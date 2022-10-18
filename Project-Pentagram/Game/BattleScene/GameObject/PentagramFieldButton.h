#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"
#include "Game/Spells/Element.h"
#include "RuneObject.h"

class PentagramFieldButton : public Button
{
private:
    enum class ButtonState
    {
        Idle = 2,
        Hover,
        Down
    };

    PentagramField m_SelectedField;
    Element::Type m_CurrentElement;
    ButtonState m_buttonState;

    UIObject* ButtonCover;
    UIObject* FieldSignature;
    UIObject* ElementSignature;

    std::vector<RuneObject*> m_RuneList;

    RuneObject* ComplexRune;

    int m_ActiveRune = 0;

    virtual void OnUpdate(const float& dt) override;
public:

    void SetActive(const bool& active) override;

    void SetToggle(bool isToggle);

    void SetRuneActive(int amount);

    PentagramField GetButtonField() const { return m_SelectedField; }

    PentagramFieldButton(PentagramField field, Element::Type element);
};