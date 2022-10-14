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

    UIObject* ButtonCover;
    UIObject* FieldSignature;
    UIObject* ElementSignature;
public:
    PentagramFieldButton(PentagramField field, Element::Type element);
};