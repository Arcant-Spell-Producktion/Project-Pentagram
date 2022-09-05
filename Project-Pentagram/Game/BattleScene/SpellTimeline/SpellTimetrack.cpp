#include "SpellTimetrack.h"

void SpellTimetrack::push_back(CastSpellDetail* spell)
{
    if (m_WillCompareTable.find(spell->SpellOwner) == m_WillCompareTable.end())
    {
        m_WillCompareTable[spell->SpellOwner] = spell->SelectedWill;
    }
    else
    {
        m_WillCompareTable[spell->SpellOwner] += spell->SelectedWill;
    }

    m_Timetrack.push_back(spell);
}

CasterPosition SpellTimetrack::GetWinCaster()
{
    CasterPosition mostWillCaster = CasterPosition::NONE;
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
    return mostWillCaster;
}

void SpellTimetrack::UpdateTimetrack()
{
    CasterPosition winCaster = GetWinCaster();
    if (winCaster <= CasterPosition::TIED)
    {
        clear();
        return;
    }

    CasterPosition lossCaster = winCaster == CasterPosition::CasterA ? CasterPosition::CasterB : CasterPosition::CasterA;
    int totalLostWill = m_WillCompareTable[lossCaster];
    for (CastSpellDetail* csd : m_Timetrack)
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

        if (totalLostWill <= 0)
        {
            break;
        }
    }
}

void SpellTimetrack::clear(bool doDelete)
{
    m_WillCompareTable.clear();

    if (doDelete)
    {
        for (CastSpellDetail* csd : m_Timetrack)
        {
            delete csd;
        }
    }

    m_Timetrack.clear();
}
