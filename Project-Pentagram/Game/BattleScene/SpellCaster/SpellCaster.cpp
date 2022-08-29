#include <iostream>
#include <cmath>
#include "SpellCaster.h"

void SpellCaster::SetUp(Element::Type element,Caster caster)
{
    m_Element = element;
    m_SpellCaster = caster;
    m_CurrentBook = SpellDatabase::GetInstance()->GetBookByElement(m_Element);
    m_PentagramData = {1,1,1,1,1};
    UpdateCurrentSpell();
}

void SpellCaster::UpdateCurrentSpell()
{
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + (m_PentagramData.complex - 1);
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    if (m_CurrentSpell != nullptr) delete m_CurrentSpell;
    m_CurrentSpell = new CastSpellDetail(m_SpellCaster,selectedSpell,m_PentagramData.will,m_PentagramData.effect, m_PentagramData.time);

    std::cout << *m_CurrentSpell->OriginalSpell << "\n\tCost: " << std::to_string(GetSpellCost()) << "\n";

}

void SpellCaster::SetPentagramData(PentagramData_T pentagram)
{
    m_PentagramData = pentagram;
    UpdateCurrentSpell();
}

void SpellCaster::CommitSpell()
{
    //TODO:: Implememnt timeline
    //SpellTimeline::GetInstance()->AddSpellToTimeline(m_CurrentSpell);
    m_CurrentSpell = nullptr;
}

int SpellCaster::GetSpellCost()
{
    int sum = 1;//All spell start with value 1

    sum += m_PentagramData.circle - 1;
    sum += m_PentagramData.complex - 1;
    sum += m_PentagramData.will - 1;
    sum += m_PentagramData.effect - 1;
    sum += std::abs(m_CurrentSpell->OriginalSpell->GetCastTime() - m_PentagramData.time);

    return sum;
}