#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

int const CasterManager::GetHealth() { return m_CurrentData.Stat().CurrentHealth; }

void CasterManager::SetHealth(int health) { m_CurrentData.Stat().CurrentHealth = health; }

void CasterManager::ChangeHealth(int health) { m_CurrentData.Stat().CurrentHealth += health; }

int const CasterManager::GetMana() { return m_CurrentData.Stat().CurrentMana; }

void CasterManager::SetMana(int mana) { m_CurrentData.Stat().CurrentMana = mana; }

void CasterManager::ChangeMana(int mana) { m_CurrentData.Stat().CurrentMana += mana; }

int CasterManager::RandomMana()
{
    int curWheel = -1;
    if (std::count(m_ManaWheelTracker.begin(), m_ManaWheelTracker.end(),false))
    {
        int index = rand() % 6;

        while (m_ManaWheelTracker[index])
        {
            index = (index + 1) % 6;
        }

        curWheel = m_CurrentData.Stat().CurrentManaWheel;
        m_CurrentData.Stat().CurrentManaWheel = index;
        m_CurrentData.Stat().MaxMana += m_CurrentData.Stat().ManaWheel[m_CurrentData.Stat().CurrentManaWheel];
        m_ManaWheelTracker[m_CurrentData.Stat().CurrentManaWheel] = true;
           
    }

    m_CurrentData.Stat().CurrentMana = m_CurrentData.Stat().MaxMana;

    return curWheel;
}

void CasterManager::ResetMana()
{
    m_CurrentData.Stat().MaxMana = 0;
    m_ManaWheelTracker = { false, false, false, false, false, false };
}

void CasterManager::SetTimeDebuff(int debuff) { m_TimeDebuff = debuff; }

void CasterManager::ResetTimeDebuff() { m_TimeDebuff = 0; }

CastSpellDetail* CasterManager::GetSpellDetail()
{
    return m_CurrentSpell;
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

    sum += (m_PentagramData.circle - 1) * 2;
    sum += (m_PentagramData.complex - 1) * 2;
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
    return  GetRemainMana() >= GetSpellCost();
}

CasterStat CasterManager::GetPreviewStat()
{
    CasterStat temp(m_CurrentData.Stat());
    temp.CurrentMana = GetRemainMana();
    return temp;
}

