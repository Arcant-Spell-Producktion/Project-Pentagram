#include "CasterEffectIconUI.h"
#include <string>
const std::string EffectIconPath = "Sprites/UI/Game/Caster/ui_game_caster_status-icon.png";

CasterEffectIconUI::CasterEffectIconUI(SpellEffectEnum type, int n):UIObject("EffectIcon_"+(int)type)
{
    m_Type = type;
    m_Stack = n;

    float size = 38.0f;

    this->scale = { size,size,1.0f };
    this->SetTexture(EffectIconPath);
    this->SetSpriteByValue(1, (int)m_Type);

    m_StackText = new TextObject(this->name + "StackText");
    m_StackText->textAlignment = TextAlignment::MID;
    m_StackText->fontSize = 16.0f;
    m_StackText->outlineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    m_StackText->position = { 10.0f, -12.0f,0.0f };

    this->SetChildRenderFront(m_StackText);

    ChangeStack(m_Stack);
}

void CasterEffectIconUI::ChangeStack(int n)
{
    m_Stack = n;
    m_StackText->text = std::to_string(m_Stack);
    this->SetActive(m_Stack > 0);
}
