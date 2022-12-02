#pragma once
#include "Engine/IGameObjectManager.h"

class CasterDetailUI :public UIObject
{
private:

    UIObject* m_Health;
    UIObject* m_Mana;

    TextObject* m_HealthText;
    TextObject* m_ManaText;

public:
    CasterDetailUI(int position);

    void SetHealthText(int cur, int max);
    void SetManaText(int cur, int max);
};