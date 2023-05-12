#include "EffectDetailUI.h"

EffectDetailUI::EffectDetailUI(int position, glm::vec3 scale, float fontSize) : UIObject("EffectDetailUI")
{
    m_Box = new UIObject("DetailBox_");
    m_Box->scale = scale;
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(position, 0);
    this->SetChildRenderFront(m_Box);

    m_TextEffectName = new TextObject("EffectDetailBox_Text_Name");
    m_TextEffectName->position.y = 45.0f;
    InitTextObjectComponent(m_TextEffectName, fontSize);

    m_TextEffectDetail = new TextObject("EffectDetailBox_Text_Detail");
    m_TextEffectDetail->position.y = 15.0f;
    InitTextObjectComponent(m_TextEffectDetail, fontSize);

    m_TextEffectDetailUtility = new TextObject("EffectDetailBox_Text_DetailUtility");
    InitTextObjectComponent(m_TextEffectDetailUtility, fontSize);

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
    // For Boost Effect
    std::stringstream ssDetailUtility;
    m_TextEffectDetailUtility->SetActive(false);

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

        case SpellEffectEnum::Fortify :
            m_TextEffectDetail->color = AC_GREEN;
            ssDetail << FortifyEffectDetail;
            break;

        case SpellEffectEnum::Petrify :
            m_TextEffectDetail->color = AC_YELLOW;
            ssDetail << PerifyEffectDetail;
            break;

        case SpellEffectEnum::Boost:
            m_TextEffectDetail->color = AC_GREEN;
            m_TextEffectDetailUtility->position.y = 15.0f;

            ssDetail << "Boost\n";
            if (details->GetStack() >= 2) { ssDetail << BoostEffectDetail[0]; m_TextEffectDetailUtility->position.y -= 30.0f; }
            else { ssDetailUtility << BoostEffectDetail[0]; }

            if (details->GetStack() >= 5) { ssDetail << "\n" << BoostEffectDetail[1]; m_TextEffectDetailUtility->position.y -= 30.0f; }
            else { ssDetailUtility << "\n" << BoostEffectDetail[1]; }
            
            if (details->GetStack() >= 8) { ssDetail << "\n" << BoostEffectDetail[2]; m_TextEffectDetailUtility->position.y -= 30.0f; }
            else { ssDetailUtility << "\n" << BoostEffectDetail[2]; }
            
            m_TextEffectDetailUtility->text = ssDetailUtility.str();
            m_TextEffectDetailUtility->SetActive(true);
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