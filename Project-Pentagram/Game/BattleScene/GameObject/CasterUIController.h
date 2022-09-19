#pragma once
#include "Game/BattleScene/BattleScene.h"
#include "Game/GameData/CasterData/CasterPosition.h"

class CasterUIController
{
private:
    int m_CurrentHealth = 0;
    int m_MaxHealth = 0;

    int m_CurrentMana = 0;
    int m_MaxMana = 0;

    TextObject* m_HealthText;
    TextObject* m_ManaText;
public:
    CasterUIController(BattleScene* scene,CasterPosition position);
    void SetHealthText(int cur, int max);
    void SetManaText(int cur, int max);
};