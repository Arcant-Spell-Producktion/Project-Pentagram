#include "SpellDetailUI.h"
#include "Engine/GameStateController.h"
#include <sstream>

void SpellDetailUI::SetText(CastSpellDetail* details)
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

    if (details != nullptr && details->OriginalSpell != nullptr)
    {
        ssName << details->OriginalSpell->GetSpellName();
        
        ssDmg << details->GetDamage() << "(" << details->SelectedWill << ")";

        auto effType = details->OriginalSpell->GetSpellEffectType();
        effName = SpellEffectType::GetString(effType);
        std::string persent = SpellEffectType::IsEffectApplyByChance(effType) ? "%" : "";
        ssEff << effName << " (" << details->GetEffectValue() << persent << ")";

        ssCha << ChannelEffectType::GetString(details->OriginalSpell->GetChannelEffectType());
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

void SpellDetailUI::InitTextObjectComponent(TextObject* textObject)
{
    textObject->fontSize = 28;
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

SpellDetailUI::SpellDetailUI(int position) : UIObject("SpellDetailUI_" + std::to_string(position))
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
    InitTextObjectComponent(m_TextSpellName);

    m_TextSpellDmg = new TextObject("DetailBox_Text_Dmg" + std::to_string(position));
    m_TextSpellDmg->position.y += 15.0f;
    InitTextObjectComponent(m_TextSpellDmg);

    m_TextSpellEff = new TextObject("DetailBox_Text_Eff" + std::to_string(position));
    m_TextSpellEff->position.y -= 15.0f;
    InitTextObjectComponent(m_TextSpellEff);

    m_TextSpellCha = new TextObject("DetailBox_Text_Cha" + std::to_string(position));
    m_TextSpellCha->position.y -= 45.0f;
    InitTextObjectComponent(m_TextSpellCha);

    m_CurrentDetails = nullptr;
    SetDetail(m_CurrentDetails,true);
}

void SpellDetailUI::SetDetail(CastSpellDetail* details, bool isDefault)
{
    CastSpellDetail* detailToUpdate = details;
    if (details == nullptr)
    {
        detailToUpdate = m_CurrentDetails;
    }

    SetText(detailToUpdate);

    if(isDefault) m_CurrentDetails = details;
}
