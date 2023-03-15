#include "SpellTimetrack.h"

void SpellTimetrack::AdjustWillAfterCompare()
{
    CasterPosition winCaster = GetWillCompareResult();

    CasterPosition lossCaster = (winCaster == CasterPosition::CasterB) ? CasterPosition::CasterA : CasterPosition::CasterB;
    int totalLostWill = m_WillCompareTable[lossCaster];
    for (CastSpellDetail* csd : m_TrackSpells)
    {
        csd->isHidden = false;

        if (csd->Channel >= CastSpellDetail::Body)
        {
            continue;
        }

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

void SpellTimetrack::SimulateSpellTrigger()
{
    CasterPosition winCaster = GetWillCompareResult();

    CasterPosition lossCaster = (winCaster == CasterPosition::CasterB) ? CasterPosition::CasterA : CasterPosition::CasterB;

    int triggerCount = 0;

    if (DoWillCompare() && winCaster > CasterPosition::TIED)
    {
        for (auto activeSpell : m_ActiveSpells)
        {
            ChannelEffectEnum activeType = activeSpell->OriginalSpell->GetChannelEffectType();
            if (activeSpell->Channel == CastSpellDetail::Head || activeType < ChannelEffectEnum::Trap)
            {
                continue;
            }

            auto it = m_TrackSpells.begin();
            for (it = m_TrackSpells.begin();it != m_TrackSpells.end(); ++it )
            {
                CastSpellDetail* spell = *it;

                //Skip spell by same caster
                if (activeSpell->SpellOwner == spell->SpellOwner)
                {
                    continue;
                }

                if (spell->TriggeredSpell != nullptr)
                {
                    continue;
                }

                if (activeType == ChannelEffectEnum::Trap)
                {
                    spell->TriggeredSpell = activeSpell;
                    activeSpell->TriggeredSpell = spell;
                }
                else if(activeType == ChannelEffectEnum::Counter && spell->OriginalSpell->GetSpellTarget() == SpellTargetEnum::Opponent)
                {
                    spell->TriggeredSpell = activeSpell;
                    activeSpell->TriggeredSpell = spell;
                }
            }

            if (it == m_TrackSpells.end())
            {
                break;
            }
        }
    }

    
}

CasterPosition SpellTimetrack::CalculateWillCompareResult(bool recalculate = false)
{
    if (recalculate || DoWillCompare() && m_WillCompareWinner == CasterPosition::NONE)
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

        m_WillCompareWinner = mostWillCaster;
    }

    return m_WillCompareWinner;
}

std::vector<CastSpellDetail*> SpellTimetrack::GetSpellResolveList()
{
    std::vector<CastSpellDetail*> ResolveTrack;

    CasterPosition winCaster = GetWillCompareResult();
    for (CastSpellDetail* spell : m_TrackSpells)
    {
        if (!spell->isCasted && spell->SpellOwner == winCaster)
        {
            ResolveTrack.push_back(spell->TriggeredSpell == nullptr? spell: spell->TriggeredSpell);
        }
    }

    return ResolveTrack;
}

void SpellTimetrack::PushSpell(CastSpellDetail* spell)
{
    bool doWillCompare = spell->DoWillCompare();
    int willValue = doWillCompare ? spell->SelectedWill : 0;

    if (m_WillCompareTable.find(spell->SpellOwner) == m_WillCompareTable.end())
    {
        m_WillCompareTable.emplace(spell->SpellOwner, willValue);
        m_SpellCount.emplace(spell->SpellOwner, 1);
    }
    else
    {
        m_WillCompareTable[spell->SpellOwner] += willValue;
        m_SpellCount[spell->SpellOwner]++;

    }

    std::cout << "Add Spell For :" << (int)spell->SpellOwner << " Total will is: " << m_WillCompareTable[spell->SpellOwner] << "\n";
    m_TrackSpells.push_back(spell);

    if (spell->Channel >= CastSpellDetail::Body)
    {
        m_ActiveSpells.push_back(spell);
    }

    CalculateWillCompareResult(true);
}

void SpellTimetrack::RemoveSpell(CastSpellDetail* spell)
{
    auto it = std::find(m_TrackSpells.begin(), m_TrackSpells.end(), spell);
    if (it != m_TrackSpells.end())
    {
        if (spell->DoWillCompare())
        {
            m_WillCompareTable[spell->SpellOwner] -= spell->SelectedWill;
        }

        m_SpellCount[spell->SpellOwner]--;

        m_TrackSpells.erase(it);
        
        if (spell->Channel >= CastSpellDetail::Body)
        {
            m_ActiveSpells.erase(std::find(m_ActiveSpells.begin(), m_ActiveSpells.end(), spell));
        }

    }
}

void SpellTimetrack::RemoveChildSpell(CastSpellDetail* parentSpell)
{
    for (CastSpellDetail* spell : m_ActiveSpells)
    {
        if (spell->ParentSpell == parentSpell)
        {
            RemoveSpell(spell);
            return;
        }
    }
}

CasterPosition SpellTimetrack::GetWillCompareResult()
{
    return CalculateWillCompareResult();
}

bool SpellTimetrack::DoWillCompare()
{
    return m_WillCompareTable[CasterPosition::CasterA] > 0 && m_WillCompareTable[CasterPosition::CasterB] > 0;
}

void SpellTimetrack::UpdateTimetrack()
{

    CasterPosition winCaster = CalculateWillCompareResult(true);
    if (winCaster <= CasterPosition::TIED)
    {
        if (m_TrackSpells.size() > 0 && DoWillCompare())
        {
            for (CastSpellDetail* csd : m_TrackSpells)
            {
                csd->isCasted = true;
                csd->isHidden = false;
            }
        }
        return;
    }

    AdjustWillAfterCompare();

    SimulateSpellTrigger();
    
}

void SpellTimetrack::clear(bool doDelete)
{
    m_WillCompareWinner = CasterPosition::NONE;

    m_SpellCount.clear();
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
