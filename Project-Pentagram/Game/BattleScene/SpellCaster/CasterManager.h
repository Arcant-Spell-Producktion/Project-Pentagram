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

    int m_WillDebuff = 0;
    int m_TimeDebuff = 0;

    int GetTimeCost();

public:
    CasterManager(CasterData caster);

    CasterData& Data() { return m_CurrentData; }

    CasterStat GetPreviewStat();

    PentagramData_T GetPentagramData() { return m_PentagramData; }

    CastSpellDetail* GetSpellDetail();

    bool SetPentagramData(PentagramData_T pentagram);

    int GetSpellCost();
    int GetFieldCost(PentagramField field);
    bool CanCastSpell();
    bool UpdateCurrentSpell();
    void CommitSpell();

    bool IsManaWheelAllUsed();

    int RandomManaWheelIndex();
    int GetManaWheelValue(int index);

    void ResetManaWheelTracker();
    void AddWheelToMana(int index);

    int const GetHealth();
    void SetHealth(int health);
    void ChangeHealth(int health);

    int GetMana();
    int GetRemainMana();
    void SetMana(int mana);
    void ChangeMana(int mana);

    int GetMaxMana();
    void ChangeMaxMana(int mana);

    void ResetMana();

    void SetWillDebuff(int debuff);

    void SetTimeDebuff(int debuff);

    void ResetDebuff();


  /*  ~CasterManager()
    {
        delete m_CurrentSpell;
    }*/
};

