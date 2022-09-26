#include "CasterUIController.h"

std::string TextFormat(int a, int b)
{
    std::string text = std::to_string(a) + "/" + std::to_string(b);
    return text;
}

CasterUIController::CasterUIController(CasterPosition position):m_Scene(GameStateController::GetInstance()->currentScene)
{
    int flip = position == CasterPosition::CasterA ? 1 : -1;
    float y_position = -460.0f;

    m_HealthText = m_Scene->CreateTextObject("m_HealthText_" + std::to_string((int)position));
    m_HealthText->textAlignment = TextAlignment::MID;
    m_HealthText->position = { -700.0f * flip, y_position, 0.0f };
    m_HealthText->color = AC_RED;
    m_HealthText->outlineColor = AC_BLACK;
    SetHealthText(0,0);
    
    glm::vec3 manaPos = { -500.0f * flip, y_position, 0.0f };
    m_Mana = m_Scene->CreateUIObject("m_Mana_" + std::to_string((int)position));
    m_Mana->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_mana-stone.png");
    m_Mana->position = manaPos;
    m_Mana->scale = {180.0f,180.0f,1.0f};

    m_ManaText = m_Scene->CreateTextObject("m_ManaText_" + std::to_string((int)position));
    m_Mana->SetChildRenderFront(m_ManaText);
    m_ManaText->fontSize = 36.0f;
    m_ManaText->outlineColor = AC_BLACK;
    m_ManaText->textAlignment = TextAlignment::RIGHT;
    m_ManaText->position = manaPos;
    m_ManaText->position.x += 45.0f;
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
