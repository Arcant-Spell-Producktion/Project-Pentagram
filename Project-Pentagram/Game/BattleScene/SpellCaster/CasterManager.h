#pragma once
#include "Utilities/Singleton.h"
#include "Game/GameData/CasterData/CasterData.h"
#include "Game/Spells/SpellDatabase.h"
#include "CastSpellDetail.h"
#include "PentagramData.h"

class CasterManager
{
private:
protected:
    CasterData m_CurrentData;
    PentagramData_T m_PentagramData;
    SpellBook* m_CurrentBook = nullptr;
    CastSpellDetail* m_CurrentSpell = nullptr;

    int m_TimeDebuff = 0;

    int GetTimeCost();
public:
    CasterManager(CasterData caster);

    CasterData& Data() { return m_CurrentData; }

    void CommitSpell();

    int GetFieldCost(PentagramField field);

    int GetSpellCost();

    int GetRemainMana();

    bool CanCastSpell();

    CasterStat GetPreviewStat();

    PentagramData_T GetPentagramData() { return m_PentagramData; }

    bool SetPentagramData(PentagramData_T pentagram);

    bool UpdateCurrentSpell();

    int const GetHealth() { return m_CurrentData.Stat().CurrentHealth; }

    void SetHealth(int health) { m_CurrentData.Stat().CurrentHealth = health; }

    void ChangeHealth(int health) { m_CurrentData.Stat().CurrentHealth += health; }

    int const GetMana() { return m_CurrentData.Stat().CurrentMana;}

    void SetMana(int mana) { m_CurrentData.Stat().CurrentMana = mana; }

    void ChangeMana(int mana) { m_CurrentData.Stat().CurrentMana += mana; }

    void ResetMana() { m_CurrentData.Stat().CurrentMana = m_CurrentData.Stat().MaxMana; }

    void SetTimeDebuff(int debuff) { m_TimeDebuff = debuff; }

    void ResetTimeDebuff() { m_TimeDebuff = 0; }

    CastSpellDetail* GetSpellDetail()
    {
       return m_CurrentSpell;
    }

  /*  ~CasterManager()
    {
        delete m_CurrentSpell;
    }*/
};

