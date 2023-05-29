#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "CasterManager.h"

CasterManager::CasterManager(CasterData caster) :m_CurrentData(caster)
{
    if (caster.Element() == Element::Corrupt)
    {
        SetCasterElement(Element::Earth);
    }
    else
    {
        SetCasterElement();
    }

    
}

CasterStat CasterManager::GetPreviewStat()
{
    CasterStat temp(m_CurrentData.Stat());
    temp.CurrentMana = GetRemainMana();
    return temp;
}

CastSpellDetail* CasterManager::GetSpellDetail()
{
    return m_CurrentSpell;
}

void CasterManager::SetCasterElement(Element::Type element)
{
    if(element != Element::NULLTYPE) m_CurrentData.Element() = element;
    m_CurrentBook = SpellDatabase::GetInstance().GetBookByElement(m_CurrentData.Element());
    m_PentagramData = { 1,1,1,1,0 };
    UpdateCurrentSpell(true);
}

int CasterManager::GetSpellCost()
{
    int sum = 1;//All spell start with value 1

    for (int i = static_cast<int>(PentagramField::Time); i <= static_cast<int>(PentagramField::Effect); i++)
    {
        sum += GetFieldCost(static_cast<PentagramField>(i));
    }

    return sum;
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
        value = (m_PentagramData.circle - 1) * 2;
        break;
    case PentagramField::Complex:
        value = (m_PentagramData.complex - 1) * 2;
        break;
    case PentagramField::Will:
        value = m_PentagramData.will - 1;
        value = value - m_WillBuff < 0 ? 0 : value - m_WillBuff;
        break;
    case PentagramField::Effect:
        value = m_PentagramData.effect - 1;
        break;
    }
    return value;
}

int CasterManager::GetFieldValue(PentagramField field)
{
    int value = 0;
    switch (field)
    {
    case PentagramField::Time:
        value = GetTimeCost();
        break;
    case PentagramField::Circle:
        value = (m_PentagramData.circle) * 2;
        break;
    case PentagramField::Complex:
        value = (m_PentagramData.complex) * 2;
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
    int timeDiff = m_PentagramData.time - m_CurrentSpell->GetSpellDetail()->GetCastTime();

    timeDiff = (timeDiff + m_TimeBuff) < 0 ? std::abs(timeDiff + m_TimeBuff) : 0;

    return  timeDiff + timeDiff * m_TimeDebuff;
}

bool CasterManager::UpdateCurrentSpell(bool isElementChange)
{
    bool isSpellChanged = false || isElementChange;
    int spellIndex = ((m_PentagramData.circle - 1) * 3) + (m_PentagramData.complex - 1);
    Spell* selectedSpell = m_CurrentBook->GetSpellByIndex(spellIndex);
    bool isSpellChange = m_CurrentSpell == nullptr || isElementChange || selectedSpell->GetSpellIndex() != m_CurrentSpell->GetIndex() ;

    if (m_PentagramData.time < 1 || isSpellChange) m_PentagramData.time = selectedSpell->GetCastTime();

    int remainWill = m_PentagramData.will - m_WillDebuff < 1 ? 1 : m_PentagramData.will - m_WillDebuff;

    if (!isSpellChange)
    {
        m_CurrentSpell->UpdateDetail(remainWill, m_PentagramData.effect, m_PentagramData.time);
    }
    else
    {
        if (m_CurrentSpell != nullptr) delete m_CurrentSpell;

        m_CurrentSpell = new CastSpellDetail
        (m_CurrentData.Position(), selectedSpell, remainWill, m_PentagramData.effect);

        isSpellChanged = true;
    }

    m_CurrentSpell->bonusDamage = m_DmgBuff;

    std::cout << "\nSelected Spell\n" << *m_CurrentSpell << "\n\tCost: " << std::to_string(GetSpellCost()) << "\n";
    return isSpellChanged;
}

void CasterManager::CommitSpell()
{
    std::cout << "COMMIT " << GetSpellCost() << "\n";
    ChangeMana(-GetSpellCost());

    //if (m_PentagramData.time < m_CurrentSpell->GetSpellDetail()->GetCastTime() && m_TimeBuff > 0)
    //{
    //    m_TimeBuff = 0;
    //}

    //if (m_PentagramData.will > 1 && m_WillBuff > 0)
    //{
    //    m_WillBuff = 0;
    //}

    m_CurrentSpell = nullptr;
}

int CasterManager::GetManaWheelValue(int index) { return  m_CurrentData.Stat().ManaWheel[index]; }

int CasterManager::RandomManaWheelIndex()
{
    int index = rand() % 6;

    while (m_ManaWheelTracker[index] && !IsManaWheelAllUsed())
    {
        index = (index + 1) % 6;
    }

    return index;
}

bool CasterManager::IsManaWheelAllUsed()
{
    return std::count(m_ManaWheelTracker.begin(), m_ManaWheelTracker.end(), false) == 0;
}

void CasterManager::ResetManaWheelTracker()
{
    m_ManaWheelTracker = { false, false, false, false, false, false };
}

void CasterManager::AddWheelToMana(int index)
{
    m_CurrentData.Stat().CurrentManaWheel = index;
    m_ManaWheelTracker[m_CurrentData.Stat().CurrentManaWheel] = true;

    ChangeMaxMana(m_CurrentData.Stat().ManaWheel[m_CurrentData.Stat().CurrentManaWheel]);

    m_CurrentData.Stat().CurrentMana = m_CurrentData.Stat().MaxMana;
}

int const CasterManager::GetHealth() { return m_CurrentData.Stat().CurrentHealth; }
void CasterManager::SetHealth(int health) { m_CurrentData.Stat().CurrentHealth = health; }
void CasterManager::ChangeHealth(int health) { m_CurrentData.Stat().CurrentHealth += health; }

int CasterManager::GetRemainMana()
{
    return GetMana() - GetSpellCost();
}

int CasterManager::GetMana() { return m_CurrentData.Stat().CurrentMana; }

void CasterManager::SetMana(int mana) { m_CurrentData.Stat().CurrentMana = mana; }

void CasterManager::ChangeMana(int mana)
{
    m_CurrentData.Stat().CurrentMana += mana;
}

int CasterManager::GetMaxMana() { return m_CurrentData.Stat().MaxMana; }

void CasterManager::ChangeMaxMana(int mana)
{
    m_CurrentData.Stat().MaxMana += mana;

    if (m_CurrentData.Stat().MaxMana > 20)
        m_CurrentData.Stat().MaxMana = 20;
}

void CasterManager::ResetMana()
{
    m_CurrentData.Stat().MaxMana = 0;
    ResetManaWheelTracker();
}

void CasterManager::SetWillBuff(int buff) { m_WillBuff = buff; }
void CasterManager::SetTimeBuff(int buff) { m_TimeBuff = buff; }
void CasterManager::SetDmgBuff(int buff) { m_DmgBuff = buff; }
void CasterManager::ResetBuff()
{
    m_WillBuff = 0;
    m_TimeBuff = 0;
    m_DmgBuff = 0;
}

void CasterManager::SetWillDebuff(int debuff) { m_WillDebuff = debuff; }
void CasterManager::SetTimeDebuff(int debuff) { m_TimeDebuff = debuff; }

void CasterManager::ResetDebuff()
{
    m_WillDebuff = 0;
    m_TimeDebuff = 0;
}

bool CasterManager::CanCastSpell()
{
    return  GetRemainMana() >= 0;
}

bool CasterManager::SetPentagramData(PentagramData_T pentagram)
{
    m_PentagramData = pentagram;
    return UpdateCurrentSpell();
}




