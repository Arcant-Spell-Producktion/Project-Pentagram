#pragma once
#include "Utilities/Singleton.h"
#include "Game/GameData/CasterData/CasterData.h"
#include "Game/Spells/SpellDatabase.h"
#include "CastSpellDetail.h"
#include "PentagramData.h"
class SpellCaster
{
private:
    void UpdateCurrentSpell();
protected:
    CasterData m_CurrentData;
    PentagramData_T m_PentagramData;
    SpellBook* m_CurrentBook = nullptr;
    CastSpellDetail* m_CurrentSpell = nullptr;

    int m_Health = 0;
    int m_Mana = 0;

public:
    SpellCaster(CasterData caster);

    CasterData* GetCasterData() { return &m_CurrentData; }

    void CommitSpell();

    int GetSpellCost();

    PentagramData_T GetPentagramData() { return m_PentagramData; }

    void SetPentagramData(PentagramData_T pentagram);

    int GetHealth() { return m_Health; }

    void SetHealth(int health) { m_Health = health; }

    void ChangeHealth(int health) { m_Health += health; }

    int GetMana() { return m_Mana; }

    void SetMana(int mana) { m_Mana = mana; }

    void ChangeMana(int mana) { m_Mana += mana; }

    void ResetMana() { m_Mana = m_CurrentData.GetMana(); }

    CastSpellDetail* GetSpellDetail()
    {
       return m_CurrentSpell;
    }

  /*  ~SpellCaster()
    {
        delete m_CurrentSpell;
    }*/
};

