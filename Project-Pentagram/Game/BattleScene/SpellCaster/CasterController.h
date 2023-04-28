#pragma once
#include "CasterManager.h"
#include "Game/BattleScene/GameObject/CasterObject.h"
#include "Game/BattleScene/SpellCaster/CasterUIController.h"
#include "Game/BattleScene/SpellCaster/CasterEffectManager.h"

enum class CasterState
{
    Idle,
    Spin,
    EndTurn,
    Passed
};

class CasterController
{
private:
    Event<CasterStat> OnStatUpdate;

protected:
    bool m_IsAlive = true;
    bool m_IsReflective = false;
    int m_IsImmune = 0;

    CasterManager m_CasterManager;
    CasterState m_CasterState = CasterState::Idle;
    CasterEffectManager m_EffectManager;
    CasterUIController m_CasterUI;

    CasterObject* m_CasterObject;
    void CasterDied();
public:

    CasterController(CasterData caster);

    void UpdateCasterUI();

    CasterObject* GetCasterObject() { return m_CasterObject; }
   
    CasterManager* GetCasterManager() { return &m_CasterManager; }

    CasterUIController* GetCasterUI() { return &m_CasterUI; }//Todo:: obsure this
    
    CasterEffectManager* GetEffectManager() { return &m_EffectManager; }

    CasterState GetState() { return m_CasterState; }

    bool IsImmune() const { return m_IsImmune > 0; }

    void SetImmune(const bool isImmune) { m_IsImmune += isImmune? 1 : -1; }

    void SetState(CasterState state) { m_CasterState = state; }

    void SetIsShowCasterDetail(bool active) { m_CasterUI.SetIsShowDetail(active); }

    bool IsShowCasterDetail() { return m_CasterUI.IsShowDetail(); }
    
    void SpinManaWheel(int forceValue = -1);

    virtual void StartTurn();

    bool SetHp(int value);

    void SetMana(int value);

    bool TakeDamage(int value);

    bool IsAlive();

    CastSpellDetail* CastSpell();

    void EndTurn(bool isPassed = false)
    {
        m_CasterState = isPassed ? CasterState::Passed : CasterState::EndTurn;
    }

    ~CasterController()
    {

    }
};