#pragma once
#include "Game/GameData/CasterData/CasterStat.h"
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/BattleScene/GameObject/CasterDetailUI.h"
#include "Game/BattleScene/GameObject/SpellDetailUI.h"

class CasterUIController
{
private:
    CasterDetailUI* m_StatUI;
    SpellDetailUI* m_DetailBox;
public:
    CasterUIController(CasterPosition position);

    void SetStat(CasterStat stat);
    void SetDetail(CastSpellDetail* detail);

};