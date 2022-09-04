#include <iostream>
#include <cmath>
#include "SpellCaster.h"

SpellCaster::SpellCaster(CasterData caster)
{
    m_CurrentData = caster;
    m_Health = m_CurrentData.GetHealth();
    m_Mana = m_CurrentData.GetMana();
    m_CurrentBook = SpellDatabase::GetInstance()->GetBookByElement(m_CurrentData.GetElement());
    m_PentagramData = {1,1,1,1,1};
    UpdateCurrentSpell();
}

void SpellCaster::UpdateCurrentSpell()
{
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + (m_PentagramData.complex - 1);
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    if (m_CurrentSpell != nullptr) delete m_CurrentSpell;
    m_CurrentSpell = new CastSpellDetail(m_CurrentData.GetPosition(),selectedSpell,m_PentagramData.will,m_PentagramData.effect, m_PentagramData.time);
}

void SpellCaster::SetPentagramData(PentagramData_T pentagram)
{
    m_PentagramData = pentagram;
    UpdateCurrentSpell();
    std::cout << "Selected Spell\n" << *m_CurrentSpell->OriginalSpell << "\n\tCost: " << std::to_string(GetSpellCost()) << "\n";
}

void SpellCaster::CommitSpell()
{
    ChangeMana(-GetSpellCost());
    m_CurrentSpell = nullptr;
    //TODO:: Implememnt timeline
    //SpellTimeline::GetInstance()->AddSpellToTimeline(m_CurrentSpell);
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