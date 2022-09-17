#include "CasterUIController.h"

std::string TextFormat(int a, int b)
{
    std::string text = std::to_string(a) + "/" + std::to_string(b);
    return text;
}

CasterUIController::CasterUIController(BattleScene* scene,CasterPosition position)
{
    int flip = position == CasterPosition::CasterA ? 1 : -1;

    m_HealthText = scene->CreateTextObject("m_HealthText_" + std::to_string((int)position));
    m_HealthText->textAlignment = TextAlignment::MID;
    m_HealthText->position = { -700.0f * flip, -280.0f, 0.0f };
    m_HealthText->color = AC_RED;
    SetHealthText(0,0);
    
    m_ManaText = scene->CreateTextObject("m_ManaText_" + std::to_string((int)position));
    m_ManaText->textAlignment = TextAlignment::MID;
    m_ManaText->position = { -500.0f * flip, -280.0f, 0.0f };
    m_ManaText->color = AC_BLUE;
    SetManaText(0, 0);
}

void CasterUIController::SetHealthText(int cur, int max)
{
    m_CurrentHealth = cur;
    m_MaxHealth = max;
    m_HealthText->text = TextFormat(m_CurrentHealth, m_MaxHealth);
}

void CasterUIController::SetManaText(int cur, int max)
{
    m_CurrentMana = cur;
    m_MaxMana = max;
    m_ManaText->text = TextFormat(m_CurrentMana, m_MaxMana);
}
