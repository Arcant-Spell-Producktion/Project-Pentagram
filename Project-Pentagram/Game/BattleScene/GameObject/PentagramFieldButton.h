#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"
#include "Game/Spells/Element.h"

class PentagramFieldButton : public Button
{
private:
    enum class ButtonState
    {
        Idle = 1,
        Hover,
        Down
    };

    PentagramField m_SelectedField;
    Element::Type m_CurrentElement;
    ButtonState m_buttonState;

    UIObject* ButtonCover;
    UIObject* FieldSignature;
    UIObject* ElementSignature;

    void OnUpdate(float dt);
public:

    void SetToggle(bool isToggle);

    PentagramField GetButtonField() const { return m_SelectedField; }

    PentagramFieldButton(PentagramField field, Element::Type element);
};