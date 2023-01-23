#include "CharacterSelectUI.h"
#include "Game\CharacterSelectScene\CharacterSelectUI.h"

CharacterSelectUI::CharacterSelectUI(Element::Type element) : UIObject(element+"_player")
{
    this->color.a = 0.0f;

    m_Caster = new CasterObject();
    m_Caster->SetCaster(CasterObjectType::Player,element,CasterPosition::CasterA);
    m_Caster->position = { 0.0f,80.0f,0.0f };

    m_SelectButton = new ScrollButton(Element::GetString(element) + "_char_select-button");
    m_SelectButton->textObject.text = Element::GetString(element);
    m_SelectButton->position = { 0.0f,-200.0f,0.0f };
    m_SelectButton->SetToggleButton(true);
    m_SelectButton->onClick.AddListener([this, element](Button* button) {OnCharacterSelect.Invoke(element); });

    this->SetChildRenderFront(m_Caster);
    this->SetChildRenderFront(m_SelectButton);
}

void CharacterSelectUI::Select()
{
    m_Caster->SetState(CasterObjectState::Cast);
    m_SelectButton->SetExpand(true);
}

void CharacterSelectUI::Deselect()
{
    m_Caster->SetState(CasterObjectState::Idle);
    m_SelectButton->SetExpand(false);
}

void CharacterSelectUI::Confirm()
{
    m_Caster->SetState(CasterObjectState::Attack);
}
