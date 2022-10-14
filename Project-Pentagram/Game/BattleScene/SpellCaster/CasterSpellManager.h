#pragma once
#include "Utilities/Singleton.h"
#include "Game/GameData/CasterData/CasterData.h"
#include "Game/Spells/SpellDatabase.h"
#include "CastSpellDetail.h"
#include "PentagramData.h"
class CasterSpellManager
{
private:
    void UpdateCurrentSpell();
protected:
    CasterData m_CurrentData;
    PentagramData_T m_PentagramData;
    SpellBook* m_CurrentBook = nullptr;
    CastSpellDetail* m_CurrentSpell = nullptr;

    int m_CurrentHealth = 0;
    int m_CurrentMana = 0;

public:
    CasterSpellManager(CasterData caster);

    CasterData* GetCasterData() { return &m_CurrentData; }

    void CommitSpell();

    int GetTimeCost();

    int GetSpellCost();

    PentagramData_T GetPentagramData() { return m_PentagramData; }

    void SetPentagramData(PentagramData_T pentagram);

    int GetHealth() { return m_CurrentHealth; }

    void SetHealth(int health) { m_CurrentHealth = health; }

    void ChangeHealth(int health) { m_CurrentHealth += health; }

    int GetMana() { return m_CurrentMana; }

    void SetMana(int mana) { m_CurrentMana = mana; }

    void ChangeMana(int mana) { m_CurrentMana += mana; }

    void ResetMana() { m_CurrentMana = m_CurrentData.GetMana(); }

    CastSpellDetail* GetSpellDetail()
    {
       return m_CurrentSpell;
    }

  /*  ~CasterSpellManager()
    {
        delete m_CurrentSpell;
    }*/
};

