#include "SpellDetailUI.h"
#include "Engine/GameStateController.h"
#include <sstream>

SpellDetailUI::SpellDetailUI(int position) :UIObject("SpellDetailUI_"+position)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int flip = position == 0 ? 1 : -1;
    float box_x = 520.0f;


    this->position = { -650.0f * flip,120.0f,0.0f };

    m_Box = scene->CreateUIObject("DetailBox_"+position);
    m_Box->scale = { -box_x * flip,220.0f,1.0f };
    m_Box->SetTexture("Sprites/UI/Game/ui_game_detail-box.png");
    m_Box->SetSpriteByIndex(position, 0);
    this->SetChildRenderFront(m_Box);

    for (size_t i = 0; i < 3; i++)
    {
       m_Texts[i] = scene->CreateTextObject("DetailBox_Text_" + i); 
       m_Texts[i]->fontSize = 28;
       m_Texts[i]->color = AC_WHITE;
       m_Texts[i]->position.x -= (box_x / 2.0f)*0.9f;
       m_Texts[i]->position.y = (i * -60.0f) + 60.0f;
       this->SetChildRenderFront(m_Texts[i]);
    }

    m_Texts[0]->text = "Name: ";
    m_Texts[1]->text = "Damage: ";
    m_Texts[2]->text = "Effect: ";
}

void SpellDetailUI::SetDetail(CastSpellDetail* details)
{
    m_CurrentDetails = details;

    if (m_CurrentDetails)
    {
        std::string effName = SpellEffectType::GetString(m_CurrentDetails->OriginalSpell->GetSpellEffectType());
        std::stringstream ssDmg;
        std::stringstream ssEff;
        ssDmg << "Damage ["<< m_CurrentDetails->SelectedWill <<"]: " << m_CurrentDetails->GetDamage();
        ssEff << "Effect [" << m_CurrentDetails->SelectedEffect << "]: " << effName << " (" << m_CurrentDetails->GetEffectValue() << ")";
        m_Texts[0]->text = "Name: " + m_CurrentDetails->OriginalSpell->GetSpellName();
        m_Texts[1]->text = ssDmg.str();
        m_Texts[2]->text = ssEff.str();
    }
}
