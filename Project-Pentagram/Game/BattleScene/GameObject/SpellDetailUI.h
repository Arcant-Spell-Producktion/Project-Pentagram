#pragma once
#include "Engine/IGameObjectManager.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>
class SpellDetailUI
{
private:
    IGameObjectManager* m_ObjectManager;

    UIObject* m_Box;
    TextObject* m_Texts[3];

    CastSpellDetail* m_CurrentDetails;

public:
    SpellDetailUI(int flip);

    void SetDetail(CastSpellDetail* details);
};