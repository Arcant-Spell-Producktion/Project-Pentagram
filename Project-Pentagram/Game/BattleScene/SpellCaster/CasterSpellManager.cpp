#include <iostream>
#include <cmath>
#include "CasterSpellManager.h"

CasterSpellManager::CasterSpellManager(CasterData caster)
{
    m_CurrentData = caster;
    m_CurrentHealth = m_CurrentData.GetHealth();
    m_CurrentMana = m_CurrentData.GetMana();
    m_CurrentBook = SpellDatabase::GetInstance()->GetBookByElement(m_CurrentData.GetElement());
    m_PentagramData = {1,1,1,1,1};
    UpdateCurrentSpell();
}

void CasterSpellManager::UpdateCurrentSpell()
{
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + (m_PentagramData.complex - 1);
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    if (m_CurrentSpell != nullptr) delete m_CurrentSpell;
    m_CurrentSpell = new CastSpellDetail(m_CurrentData.GetPosition(),selectedSpell,m_PentagramData.will,m_PentagramData.effect, m_PentagramData.time);
}

void CasterSpellManager::SetPentagramData(PentagramData_T pentagram)
{
    m_PentagramData = pentagram;
    UpdateCurrentSpell();
    std::cout << "\nSelected Spell\n" << *m_CurrentSpell << "\n\tCost: " << std::to_string(GetSpellCost()) << "\n";
}

void CasterSpellManager::CommitSpell()
{
    ChangeMana(-GetSpellCost());
    m_CurrentSpell = nullptr;
    //TODO:: Implememnt timeline
    //SpellTimeline::GetInstance()->AddSpellToTimeline(m_CurrentSpell);
}

int CasterSpellManager::GetTimeCost()
{
    return std::abs(m_CurrentSpell->OriginalSpell->GetCastTime() - m_PentagramData.time);
}

int CasterSpellManager::GetSpellCost()
{

    int sum = 1;//All spell start with value 1

    sum += m_PentagramData.circle - 1;
    sum += m_PentagramData.complex - 1;
    sum += m_PentagramData.will - 1;
    sum += m_PentagramData.effect - 1;
    sum += GetTimeCost();

    return sum;
}