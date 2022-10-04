#include "SpellDetailUI.h"
#include "Engine/GameStateController.h"
#include <sstream>

SpellDetailUI::SpellDetailUI(int flip) :m_Scene(GameStateController::GetInstance()->currentScene)
{
    m_Box = m_Scene->CreateUIObject("DetailBox");
    m_Box->position = { flip* -650.0f,120.0f,0.0f };
   
    
    m_Box->scale = { 520.0f,220.0f,1.0f };
    m_Box->color = flip == 1?AC_RED:AC_BLUE;

    for (size_t i = 0; i < 3; i++)
    {
       m_Texts[i] = m_Scene->CreateTextObject("DetailBox_Text_" + i); \
       m_Texts[i]->fontSize = 36;
       m_Texts[i]->color = AC_WHITE;
       m_Texts[i]->position.x = m_Box->position.x - (m_Box->scale.x / 2.0f)*0.9f;
       m_Texts[i]->position.y = m_Box->position.y + (i * 60.0f) - 60.0f;
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
        ssDmg << "Damage: " << m_CurrentDetails->GetDamage();
        ssEff << "Effect: " << effName << " (" << m_CurrentDetails->GetEffectValue() << ")";
        m_Texts[2]->text = "Name: " + m_CurrentDetails->OriginalSpell->GetSpellName();
        m_Texts[1]->text = ssDmg.str();
        m_Texts[0]->text = ssEff.str();
    }
}
