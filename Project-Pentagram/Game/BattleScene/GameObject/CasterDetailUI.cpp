#include "CasterDetailUI.h"
#include "Engine/GameStateController.h"

std::string TextFormat(int a, int b)
{
    std::string text = std::to_string(a) + "/" + std::to_string(b);
    return text;
}

CasterDetailUI::CasterDetailUI(int position):UIObject("m_CasterBar_" + std::to_string((int)position))
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int flip = position == 0 ? 1 : -1;

    this->position = { -660.0f * flip, -455.0f , 0.0f };
    this->scale = { 420.0f, 170.0f , 1.0f };
    this->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_bar-background.png");
    this->SetSpriteByIndex(position, 0);

    m_Health = new UIObject("m_Health_" + std::to_string((int)position));
    m_Health->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_hp-bar.png");
    m_Health->SetStartGradientTexture("Sprites/GradientMap/gradiant-map_green.png");
    m_Health->SetEndGradientTexture("Sprites/GradientMap/gradiant-map_red.png");
    m_Health->SetIsGradient(true);
    m_Health->position = { 40.0f * flip , -16.0f , 0.0f };
    m_Health->scale = { 280.0f, 70.0f, 1.0f };
    m_Health->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    this->SetChildRenderFront(m_Health);

    m_Mana = new UIObject("m_Mana_" + std::to_string((int)position));
    m_Mana->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_mana-stone.png");
    m_Mana->position = { -113.0f * flip , 0.0f , 0.0f };
    m_Mana->scale = { 140.0f,140.0f,1.0f };
    this->SetChildRenderFront(m_Mana);

    m_HealthText = new TextObject("m_HealthText_" + std::to_string((int)position));
    m_HealthText->fontSize = 32.0f;
    m_HealthText->outlineColor = AC_BLACK;
    m_HealthText->textAlignment = TextAlignment::MID;
    m_Health->SetChildRenderFront(m_HealthText);
    
    m_ManaText = new TextObject("m_ManaText_" + std::to_string((int)position));
    m_ManaText->fontSize = 32.0f;
    m_ManaText->outlineColor = AC_BLACK;
    m_ManaText->textAlignment = TextAlignment::MID;
    //m_ManaText->position.x += 45.0f;
    m_Mana->SetChildRenderFront(m_ManaText);

    m_EffectBar = new CasterEffectBarUI(position);
    m_EffectBar->position = { -16.0f * flip ,32.0f,0.0f };
    this->SetChildRenderFront(m_EffectBar);

    SetHealthText(0, 0);
    SetManaText(0, 0);
}

void CasterDetailUI::SetHealthText(int cur, int max)
{
    m_HealthText->text = TextFormat(cur, max);
    m_Health->SetGradientValue(1.0f - cur / (float)max);
}

void CasterDetailUI::SetManaText(int cur, int max)
{
    m_ManaText->text = TextFormat(cur, max);
}

void CasterDetailUI::SetEffectBar(std::vector<EffectDetail_T> effects)
{
    m_EffectBar->UpdateEffectIcons(effects);
}
