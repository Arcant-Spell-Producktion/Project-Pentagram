#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/BattleScene/GameObject/SpellDetailUI.h"

class CasterUIController
{
private:
    IGameObjectManager* m_ObjectManager;

    int m_CurrentHealth = 0;
    int m_MaxHealth = 0;

    int m_CurrentMana = 0;
    int m_MaxMana = 0;

    UIObject* m_CasterBar;

    UIObject* m_Health;
    UIObject* m_Mana;

    TextObject* m_HealthText;
    TextObject* m_ManaText;

    SpellDetailUI* m_DetailBox;
public:
    CasterUIController(CasterPosition position);
    void SetHealthText(int cur, int max);
    void SetManaText(int cur, int max);

    void SetDetail(CastSpellDetail* detail) { m_DetailBox->SetDetail(detail); };

    ~CasterUIController() { delete m_DetailBox; }
};