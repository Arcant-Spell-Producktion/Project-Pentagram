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

    std::array<bool, 6> m_ManaWheelTracker = { false, false, false, false, false, false };

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

    int const GetHealth();

    void SetHealth(int health);

    void ChangeHealth(int health);

    int const GetMana();

    void SetMana(int mana);

    void ChangeMana(int mana);

    int RandomMana();

    void ResetMana();

    void SetTimeDebuff(int debuff);

    void ResetTimeDebuff();

    CastSpellDetail* GetSpellDetail();

  /*  ~CasterManager()
    {
        delete m_CurrentSpell;
    }*/
};

