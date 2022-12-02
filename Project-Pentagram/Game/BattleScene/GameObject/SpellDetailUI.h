#pragma once
#include "Engine/IGameObjectManager.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>

class SpellDetailUI :public UIObject
{
private:
    UIObject* m_Box;
    TextObject* m_Texts[3];

    CastSpellDetail* m_CurrentDetails;

public:
    SpellDetailUI(int position);

    void SetDetail(CastSpellDetail* details);
};