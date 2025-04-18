#pragma once
#include "Game/BattleScene/GameObject/CasterEffectBarUI.h"
#include "Game/BattleScene/GameObject/EffectDetailUI.h"

class CasterDetailUI :public UIObject
{
private:

    UIObject* m_Health;
    UIObject* m_Mana;

    TextObject* m_HealthText;
    TextObject* m_ManaText;

    CasterEffectBarUI* m_EffectBar;
    EffectDetailUI* m_EffectDetailUI;

public:
    CasterDetailUI(int position);

    void OnUpdate(const float& dt) override;

    void SetHealthText(int cur, int max);
    void SetManaText(int cur, int max);
    void SetEffectBar(std::vector<EffectDetail_T> effects);
};