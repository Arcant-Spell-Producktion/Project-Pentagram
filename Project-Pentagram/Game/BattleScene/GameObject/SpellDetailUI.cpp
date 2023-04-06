#include "SpellDetailUI.h"
#include "Engine/GameStateController.h"
#include <sstream>

void SpellDetailUI::SetText(CastSpellDetail* details, bool isHideInfo)
{

    std::stringstream ssName;
    std::stringstream ssDmg;
    std::stringstream ssEff;
    std::stringstream ssCha;

    std::string effName = "<EffectName>: ";

    ssName << "Name: ";
    ssDmg << "Damage: ";
    ssEff << "Effect: ";
    ssCha << "Channel Type: ";

    if (details != nullptr && details->GetSpellDetail() != nullptr)
    {
        if (isHideInfo)
        {
            ssName << "?";

            ssDmg << "?" << " (" << details->SelectedWill << ")";

            auto effType = details->GetSpellDetail()->GetSpellEffectType();
            effName = SpellEffectType::GetString(effType);
            std::string persent = SpellEffectType::IsEffectApplyByChance(effType) ? "%" : "";
            ssEff << "?" << " (" << details->GetEffectValue() << persent << ")";

            ssCha << "?";
        }
        else
        {
            ssName << details->GetSpellDetail()->GetSpellName();
        
            ssDmg << details->GetDamage() << "(" << details->SelectedWill << ")";

            auto effType = details->GetSpellDetail()->GetSpellEffectType();
            effName = SpellEffectType::GetString(effType);
            std::string persent = SpellEffectType::IsEffectApplyByChance(effType) ? "%" : "";
            ssEff << effName << " (" << details->GetEffectValue() << persent << ")";

            ssCha << ChannelEffectType::GetString(details->GetSpellDetail()->GetChannelEffectType());
        }

    }
    else
    {
        ssName << "<SpellName>";
        ssDmg << "<Damage> (<Will>)";
        ssEff << effName << " (<EffValue>)";
        ssCha << "<ChannelType>";
    }

    InsertSpellDetailUI(m_TextSpellName, ssName.str());
    InsertSpellDetailUI(m_TextSpellDmg, ssDmg.str());
    InsertSpellDetailUI(m_TextSpellEff, ssEff.str());
    InsertSpellDetailUI(m_TextSpellCha, ssCha.str());
}

void SpellDetailUI::InitTextObjectComponent(TextObject* textObject, float fontSize)
{
    textObject->fontSize = fontSize;
    textObject->color = AC_WHITE;
    textObject->outlineColor = AC_BLACK;
    textObject->textAlignment = TextAlignment::MID;
    m_Box->SetChildRenderFront(textObject);
}

void SpellDetailUI::InsertSpellDetailUI(TextObject* textObject, const std::string& newStr)
{
    if (textObject->text != "" && textObject->text != newStr)
    {
        textObject->color = AC_YELLOW;
    }
    else
    {
        textObject->color = AC_WHITE;
    }
    textObject->text = newStr;
}

SpellDetailUI::SpellDetailUI(int position, float fontSize) : UIObject("SpellDetailUI_" + std::to_string(position))
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int flip = position == 0 ? 1 : -1;
    float box_x = 520.0f;

    m_DefaultPosition = { -650.0f * flip,120.0f,0.0f };
    this->position = m_DefaultPosition;

    m_Box = new UIObject("DetailBox_" + std::to_string(position));
    m_Box->scale = { -box_x * flip,220.0f,1.0f };
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(position, 0);
    this->SetChildRenderFront(m_Box);

    m_TextSpellName = new TextObject("DetailBox_Text_Name" + std::to_string(position));
    m_TextSpellName->position.y += 45.0f;
    InitTextObjectComponent(m_TextSpellName, fontSize);

    m_TextSpellDmg = new TextObject("DetailBox_Text_Dmg" + std::to_string(position));
    m_TextSpellDmg->position.y += 15.0f;
    InitTextObjectComponent(m_TextSpellDmg, fontSize);

    m_TextSpellEff = new TextObject("DetailBox_Text_Eff" + std::to_string(position));
    m_TextSpellEff->position.y -= 15.0f;
    InitTextObjectComponent(m_TextSpellEff, fontSize);

    m_TextSpellCha = new TextObject("DetailBox_Text_Cha" + std::to_string(position));
    m_TextSpellCha->position.y -= 45.0f;
    InitTextObjectComponent(m_TextSpellCha, fontSize);

    m_CurrentDetails = nullptr;
    SetDetail(m_CurrentDetails,true);
}
SpellDetailUI::SpellDetailUI(glm::vec3 position, glm::vec3 scale, float fontSize) : UIObject("SpellDetailUI_")
{
    auto scene = GameStateController::GetInstance()->currentScene;

    this->position = position;

    m_Box = new UIObject("DetailBox_");
    m_Box->scale = scale;
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(0, 0);
    this->SetChildRenderFront(m_Box);

    m_TextSpellName = new TextObject("DetailBox_Text_Name");
    m_TextSpellName->position.y += 45.0f;
    InitTextObjectComponent(m_TextSpellName, fontSize);

    m_TextSpellDmg = new TextObject("DetailBox_Text_Dmg");
    m_TextSpellDmg->position.y += 15.0f;
    InitTextObjectComponent(m_TextSpellDmg, fontSize);

    m_TextSpellEff = new TextObject("DetailBox_Text_Eff");
    m_TextSpellEff->position.y -= 15.0f;
    InitTextObjectComponent(m_TextSpellEff, fontSize);

    m_TextSpellCha = new TextObject("DetailBox_Text_Cha");
    m_TextSpellCha->position.y -= 45.0f;
    InitTextObjectComponent(m_TextSpellCha, fontSize);

    m_CurrentDetails = nullptr;
    SetDetail(m_CurrentDetails, true);
}


void SpellDetailUI::SetCasterPosition(CasterPosition position)
{
    m_Box->SetSpriteByValue((int)position, 1);

    m_TextSpellDmg->color = AC_RED;
    m_TextSpellEff->color = AC_YELLOW;
}
void SpellDetailUI::SetDetail(CastSpellDetail* details, bool isDefault, bool isHideInfo)
{
    CastSpellDetail* detailToUpdate = details;
    if (details == nullptr)
    {
        detailToUpdate = m_CurrentDetails;
    }

    SetText(detailToUpdate, isHideInfo);

    if(isDefault) m_CurrentDetails = details;
}
