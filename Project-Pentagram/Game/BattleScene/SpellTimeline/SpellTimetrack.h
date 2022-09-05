#pragma once
#include <vector>
#include <map>
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellTimetrack
{
private:
    vector<CastSpellDetail*> m_Timetrack;
    map<CasterPosition, int> m_WillCompareTable;
public:

    vector<CastSpellDetail*> GetSpellList() { return m_Timetrack; }

    int GetCasterWill(CasterPosition caster)
    {
        return m_WillCompareTable[caster]; 
    }

    void push_back(CastSpellDetail* spell);

    CasterPosition GetWinCaster();

    void UpdateTimetrack();

    void clear(bool doDelete = true);
};