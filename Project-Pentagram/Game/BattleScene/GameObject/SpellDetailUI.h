#pragma once
#include "Engine/GameScene.h"
#include <Game/BattleScene/SpellCaster/CastSpellDetail.h>
class SpellDetailUI
{
private:
    GameScene* m_Scene;

    UIObject* m_Box;
    TextObject* m_Texts[3];

    CastSpellDetail* m_CurrentDetails;

public:
    SpellDetailUI(int flip);

    void SetDetail(CastSpellDetail* details);
};