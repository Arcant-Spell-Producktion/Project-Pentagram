#include <iostream>
#include <cmath>
#include "CasterManager.h"

CasterManager::CasterManager(CasterData caster):m_CurrentData(caster)
{
    m_CurrentBook = SpellDatabase::GetInstance()->GetBookByElement(m_CurrentData.Element());
    m_PentagramData = {1,1,1,1,0};
    UpdateCurrentSpell();
}

bool CasterManager::UpdateCurrentSpell()
{
    bool isSpellChanged = false;
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + (m_PentagramData.complex - 1);
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    bool isSpellChange = m_CurrentSpell == nullptr || selectedSpell->GetSpellIndex() != m_CurrentSpell->GetIndex();

    if (m_PentagramData.time < 1 || isSpellChange) m_PentagramData.time = selectedSpell->GetCastTime();

    if (!isSpellChange)
    {
        m_CurrentSpell->UpdateDetail(m_PentagramData.will, m_PentagramData.effect, m_PentagramData.time);
    }
    else
    {
        if (m_CurrentSpell != nullptr) delete m_CurrentSpell;

        m_CurrentSpell = new CastSpellDetail
            (m_CurrentData.Position(), selectedSpell, m_PentagramData.will, m_PentagramData.effect);
        
        isSpellChanged = true;
    }
    std::cout << "\nSelected Spell\n" << *m_CurrentSpell << "\n\tCost: " << std::to_string(GetSpellCost()) << "\n";
    return isSpellChanged;
}

bool CasterManager::SetPentagramData(PentagramData_T pentagram)
{
    m_PentagramData = pentagram;
    return UpdateCurrentSpell();
}

void CasterManager::CommitSpell()
{
    ChangeMana(-GetSpellCost());
    m_CurrentSpell = nullptr;
    //TODO:: Implememnt timeline
    //SpellTimeline::GetInstance()->AddSpellToTimeline(m_CurrentSpell);
}

int CasterManager::GetFieldCost(PentagramField field)
{
    int value = 0;
    switch (field)
    {
    case PentagramField::Time:
        value = GetTimeCost();
        break;
    case PentagramField::Circle:
        value = m_PentagramData.circle;
        break;
    case PentagramField::Complex:
        value = m_PentagramData.complex;
        break;
    case PentagramField::Will:
        value = m_PentagramData.will;
        break;
    case PentagramField::Effect:
        value = m_PentagramData.effect;
        break;
    }
    return value;
}

int CasterManager::GetTimeCost()
{
    int timeDiff = std::abs(m_CurrentSpell->OriginalSpell->GetCastTime() - m_PentagramData.time);
    return  timeDiff  + timeDiff * m_TimeDebuff;
}

int CasterManager::GetSpellCost()
{

    int sum = 1;//All spell start with value 1

    sum += m_PentagramData.circle - 1;
    sum += m_PentagramData.complex - 1;
    sum += m_PentagramData.will - 1;
    sum += m_PentagramData.effect - 1;
    sum += GetTimeCost();

    return sum;
}

int CasterManager::GetRemainMana()
{
    return GetMana() - GetSpellCost();
}

bool CasterManager::CanCastSpell()
{
    return GetSpellCost() >= GetRemainMana();
}
