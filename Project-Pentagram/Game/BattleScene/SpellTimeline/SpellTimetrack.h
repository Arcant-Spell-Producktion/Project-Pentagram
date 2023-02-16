#pragma once
#include <vector>
#include <map>
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellTimetrack
{
private:
    std::vector<CastSpellDetail*> m_TrackSpells;
    std::map<CasterPosition, int> m_WillCompareTable;
    std::map<CasterPosition, int> m_SpellCount;
public:

    std::vector<CastSpellDetail*> GetSpellList() { return m_TrackSpells; }

    int GetCasterWill(CasterPosition caster)
    {
        return m_WillCompareTable[caster]; 
    }

    void push_back(CastSpellDetail* spell,bool doWillCompare);

    CasterPosition GetWillCompareResult();

    bool DoWillCompare();

    void UpdateTimetrack();

    void clear(bool doDelete = true);
};