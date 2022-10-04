#pragma once
#include <vector>
#include <map>
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellTimetrack
{
private:
    vector<CastSpellDetail*> m_TrackSpells;
    map<CasterPosition, int> m_WillCompareTable;
public:

    vector<CastSpellDetail*> GetSpellList() { return m_TrackSpells; }

    int GetCasterWill(CasterPosition caster)
    {
        return m_WillCompareTable[caster]; 
    }

    void push_back(CastSpellDetail* spell,bool doWillCompare);

    CasterPosition GetWillCompareResult();

    void UpdateTimetrack();

    void clear(bool doDelete = true);
};