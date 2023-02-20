#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"
#include "Game/BattleScene/GameObject/RuneObject.h"
#include "Game/Spells/Element.h"

class PentagramFieldButton : public Button
{
public: 
    enum class ButtonState
    {
        Idle = 2,
        Hover,
        Down
    };
private:

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

    void SetElement(Element::Type element);

    void SetActive(const bool& active) override;

    void SetToggle(bool isToggle);

    void SetRuneActive(int amount);

    void SetRuneColor(glm::vec4 runeColor);

    PentagramField GetButtonField() const { return m_SelectedField; }
    ButtonState GetButtonState() const { return m_buttonState; }

    PentagramFieldButton(PentagramField field, Element::Type element);
};