#pragma once
#include "Game/BattleScene/BattleScene.h"
#include "Game/GameData/CasterData/CasterPosition.h"

class CasterUIController
{
private:
    GameScene* m_Scene;

    int m_CurrentHealth = 0;
    int m_MaxHealth = 0;

    int m_CurrentMana = 0;
    int m_MaxMana = 0;

    UIObject* m_Health;
    UIObject* m_Mana;

    TextObject* m_HealthText;
    TextObject* m_ManaText;
public:
    CasterUIController(CasterPosition position);
    void SetHealthText(int cur, int max);
    void SetManaText(int cur, int max);
};