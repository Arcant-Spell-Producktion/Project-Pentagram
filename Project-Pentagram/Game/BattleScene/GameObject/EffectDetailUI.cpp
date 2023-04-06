#include "EffectDetailUI.h"

EffectDetailUI::EffectDetailUI(int position, glm::vec3 scale, float fontSize) : UIObject("EffectDetailUI")
{
    m_Box = new UIObject("DetailBox_");
    m_Box->scale = scale;
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(position, 0);
    this->SetChildRenderFront(m_Box);

    m_TextEffectName = new TextObject("EffectDetailBox_Text_Name");
    m_TextEffectName->position.y += 45.0f;
    InitTextObjectComponent(m_TextEffectName, fontSize);

    m_TextEffectDetail = new TextObject("EffectDetailBox_Text_Detail");
    m_TextEffectDetail->position.y += 15.0f;
    InitTextObjectComponent(m_TextEffectDetail, fontSize);

    m_CurrentDetails = nullptr;
}
void EffectDetailUI::SetDetail(CasterEffectIconUI* details, bool isDefault)
{
    CasterEffectIconUI* detailToUpdate = details;
    if (details == nullptr)
    {
        detailToUpdate = m_CurrentDetails;
    }

    SetText(detailToUpdate);

    if (isDefault) m_CurrentDetails = details;
}

void EffectDetailUI::SetText(CasterEffectIconUI* details)
{
    std::stringstream ssName;
    std::stringstream ssDetail;

    SpellEffectEnum effectType = details->GetEffectType();

    ssName << "Effect Name: " << SpellEffectType::GetString(effectType);
    ssDetail << "Effect: ";
    switch (effectType)
    {
        case SpellEffectEnum::Burn :
            m_TextEffectDetail->color = AC_RED;
            ssDetail << BurnEffectDetail;
            break;

        case SpellEffectEnum::Mark :
            m_TextEffectDetail->color = AC_RED;
            ssDetail << MarkEffectDetail;
            break;

        case SpellEffectEnum::Freeze :
            m_TextEffectDetail->color = AC_YELLOW;
            ssDetail << FreezeEffectDetail;
            break;

        case SpellEffectEnum::Overflow :
            m_TextEffectDetail->color = AC_GREEN;
            ssDetail << OverflowEffectDetail;
            break;
    }

    m_TextEffectName->text = ssName.str();
    m_TextEffectDetail->text = ssDetail.str();
}
void EffectDetailUI::InitTextObjectComponent(TextObject* textObject, float fontSize)
{
    textObject->fontSize = fontSize;
    textObject->color = AC_WHITE;
    textObject->outlineColor = AC_BLACK;
    textObject->textAlignment = TextAlignment::MID;
    m_Box->SetChildRenderFront(textObject);
}