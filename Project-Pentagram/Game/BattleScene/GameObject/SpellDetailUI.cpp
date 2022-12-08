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

    if (details != nullptr)
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

    m_Texts->text = ssName.str() + "\n" + ssDmg.str() + "\n" + ssEff.str() + "\n"+ ssCha.str() + "\n";
}

SpellDetailUI::SpellDetailUI(int position) :UIObject("SpellDetailUI_"+position)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int flip = position == 0 ? 1 : -1;
    float box_x = 520.0f;

    m_DefaultPosition = { -650.0f * flip,120.0f,0.0f };
    this->position = m_DefaultPosition;

    m_Box = scene->CreateUIObject("DetailBox_"+position);
    m_Box->scale = { -box_x * flip,220.0f,1.0f };
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(position, 0);
    this->SetChildRenderFront(m_Box);

    m_Texts = scene->CreateTextObject("DetailBox_Text_" + position);
    m_Texts->fontSize = 28;
    m_Texts->color = AC_WHITE;
    m_Texts->outlineColor = AC_BLACK;
    m_Texts->textAlignment = TextAlignment::MID;
    m_Texts->position.y += 50.0f;
    m_Box->SetChildRenderFront(m_Texts);

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
