#include "Engine/GameStateController.h"
#include "CasterUIController.h"

std::string TextFormat(int a, int b)
{
    std::string text = std::to_string(a) + "/" + std::to_string(b);
    return text;
}

CasterUIController::CasterUIController(CasterPosition position):m_ObjectManager(GameStateController::GetInstance()->currentScene)
{
    int flip = position == CasterPosition::CasterA ? 1 : -1;
    float y_position = -460.0f;

    m_CasterBar = m_ObjectManager->CreateUIObject("m_CasterBar_" + std::to_string((int)position));

    glm::vec3 hpPos = { -700.0f * flip, y_position - 20.0f, 0.0f };
    m_Health = m_ObjectManager->CreateUIObject("m_Health_" + std::to_string((int)position));
    m_Health->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_hp-bar.png");
    m_Health->SetStartGradientTexture("Sprites/GradientMap/gradiant-map_green.png");
    m_Health->SetEndGradientTexture("Sprites/GradientMap/gradiant-map_red.png");
    m_Health->SetIsGradient(true);
    m_Health->position = hpPos;
    m_Health->scale = { 440.0f, 110.0f, 1.0f };
    m_Health->color = { 1.0f, 1.0f, 1.0f, 1.0f };

    m_HealthText = m_ObjectManager->CreateTextObject("m_HealthText_" + std::to_string((int)position));
    m_HealthText->textAlignment = TextAlignment::MID;
    m_HealthText->position = hpPos;
    m_HealthText->outlineColor = AC_BLACK;
    SetHealthText(0,0);
    
    glm::vec3 manaPos = { -500.0f * flip, y_position, 0.0f };
    m_Mana = m_ObjectManager->CreateUIObject("m_Mana_" + std::to_string((int)position));
    m_Mana->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_mana-stone.png");
    m_Mana->position = manaPos;
    m_Mana->scale = {180.0f,180.0f,1.0f};

    m_ManaText = m_ObjectManager->CreateTextObject("m_ManaText_" + std::to_string((int)position));
    m_ManaText->fontSize = 36.0f;
    m_ManaText->outlineColor = AC_BLACK;
    m_ManaText->textAlignment = TextAlignment::RIGHT;
    m_ManaText->position = manaPos;
    m_ManaText->position.x += 45.0f;
    m_Mana->SetChildRenderFront(m_ManaText);
    SetManaText(0, 0);

    m_DetailBox = new SpellDetailUI(flip);
}

void CasterUIController::SetHealthText(int cur, int max)
{
    m_CurrentHealth = cur;
    m_MaxHealth = max;
    m_HealthText->text = TextFormat(m_CurrentHealth, m_MaxHealth);
    m_Health->SetGradientValue(1.0f - m_CurrentHealth / (float)m_MaxHealth);
}

void CasterUIController::SetManaText(int cur, int max)
{
    m_CurrentMana = cur;
    m_MaxMana = max;
    m_ManaText->text = TextFormat(m_CurrentMana, m_MaxMana);
}
