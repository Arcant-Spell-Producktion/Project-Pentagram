#include "SpellTimetrack.h"

void SpellTimetrack::push_back(CastSpellDetail* spell, bool doWillCompare = true)
{
    int willValue = doWillCompare ? spell->SelectedWill : 0;

    if (m_WillCompareTable.find(spell->SpellOwner) == m_WillCompareTable.end())
    {
        m_WillCompareTable.emplace(spell->SpellOwner, willValue);
    }
    else
    {
        m_WillCompareTable[spell->SpellOwner] += willValue;
    }

    std::cout << "Add Spell For :" << (int)spell->SpellOwner<< " Total will is: "<< m_WillCompareTable[spell->SpellOwner] << "\n";
    m_TrackSpells.push_back(spell);
}

CasterPosition SpellTimetrack::GetWillCompareResult()
{
    CasterPosition mostWillCaster = CasterPosition::NONE;
    if (m_TrackSpells.size() > 0)
    {
        for (auto it = m_WillCompareTable.begin(); it != m_WillCompareTable.end(); it++)
        {
            if (mostWillCaster == CasterPosition::NONE)
            {
                mostWillCaster = it->first;
            }
            else if (m_WillCompareTable[mostWillCaster] < it->second)
            {
                mostWillCaster = it->first;
            }
            else if (m_WillCompareTable[mostWillCaster] == it->second && mostWillCaster != it->first)
            {
                mostWillCaster = CasterPosition::TIED;
            }
        }
    }

    return mostWillCaster;
}

void SpellTimetrack::UpdateTimetrack()
{
    CasterPosition winCaster = GetWillCompareResult();
    if (winCaster <= CasterPosition::TIED)
    {
        if (m_TrackSpells.size() > 0)
        {
            for (CastSpellDetail* csd : m_TrackSpells)
            {
                csd->isCasted = true;
            }
        }
        return;
    }

    CasterPosition lossCaster = (winCaster == CasterPosition::CasterB) ? CasterPosition::CasterA : CasterPosition::CasterB;
    int totalLostWill = m_WillCompareTable[lossCaster];
    for (CastSpellDetail* csd : m_TrackSpells)
    {
        if (csd->SpellOwner == lossCaster)
        {
            csd->isCasted = true;
        }

        if (totalLostWill <= 0)
        {
            continue;
        }

        if (csd->SpellOwner == winCaster)
        {
            int currentWill = csd->SelectedWill;
            if (currentWill > 1)
            {
                int extraWill = currentWill - 1;
                if (totalLostWill - extraWill >= 0)
                {
                    csd->SelectedWill -= extraWill;
                    totalLostWill -= extraWill;
                }
                else
                {
                    csd->SelectedWill -= totalLostWill;
                    totalLostWill = 0;
                }
            }
        } 
    }
}

void SpellTimetrack::clear(bool doDelete)
{
    m_WillCompareTable.clear();

    if (doDelete)
    {
        for (CastSpellDetail* csd : m_TrackSpells)
        {
            delete csd;
        }
    }

    m_TrackSpells.clear();
}
