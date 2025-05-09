﻿#pragma once
#include <vector>
#include <map>
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellTimetrack
{
private:
    CasterPosition m_WillCompareWinner = CasterPosition::NONE;

    std::vector<CastSpellDetail*> m_TrackSpells;
    std::vector<CastSpellDetail*> m_ActiveSpells;

    std::map<CasterPosition, int> m_WillCompareTable;
    std::map<CasterPosition, int> m_SpellCount;

    void AdjustWillAfterCompare();

    void SimulateSpellTrigger();

    CasterPosition CalculateWillCompareResult(bool recalculate);
public:

    std::vector<CastSpellDetail*> GetSpellList() { return m_TrackSpells; }

    std::vector<CastSpellDetail*> GetSpellResolveList();

    int GetCasterWill(CasterPosition caster)
    {
        return m_WillCompareTable[caster]; 
    }

    bool IsTrackFull(CasterPosition caster)
    {
        return m_SpellCount[caster] >= 5;
    }

    void PushSpell(CastSpellDetail* spell);

    CastSpellDetail* RemoveSpell(CastSpellDetail* spell);

    CastSpellDetail* RemoveChildSpell(CastSpellDetail* parentSpell);

    CasterPosition GetWillCompareResult();

    bool DoWillCompare();

    void UpdateTimetrack();

    void clear(bool doDelete = true);
};