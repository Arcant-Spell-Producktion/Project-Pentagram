#include <cmath>
#include "SpellCasterController.h"

void SpellCasterController::Init(Element::Type element,Caster caster)
{
    m_Element = element;
    m_CurrentBook = SpellDatabase::GetInstance()->GetBookByElement(m_Element);
    m_SpellCaster = caster;
    m_isInit = true;
    UpdateCurrentSpell();
}

void SpellCasterController::UpdateCurrentSpell()
{
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + m_PentagramData.complex;
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    if (m_CurrentSpell != nullptr) delete m_CurrentSpell;
    m_CurrentSpell = new CastSpellDetail(m_SpellCaster,selectedSpell,m_PentagramData.will,m_PentagramData.effect, m_PentagramData.time);
}

void SpellCasterController::SetPentagramData(PentagramData pentagram)
{
    m_PentagramData = pentagram;
    UpdateCurrentSpell();
}

void SpellCasterController::CommitSpell()
{
    //TODO:: Implememnt timeline
    //SpellTimeline::GetInstance()->AddSpellToTimeline(m_CurrentSpell);
    m_CurrentSpell = nullptr;
}

int SpellCasterController::GetSpellCost()
{
    int sum = 0;

    sum += m_PentagramData.circle - 1;
    sum += m_PentagramData.complex - 1;
    sum += m_PentagramData.will - 1;
    sum += m_PentagramData.effect - 1;
    sum += (m_CurrentSpell->OriginalSpell->GetCastTime() - m_PentagramData.time);

    return sum;
}