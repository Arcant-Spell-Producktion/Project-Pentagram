#pragma once
#include "CasterManager.h"
#include "Game/BattleScene/GameObject/CasterObject.h"
#include "Game/BattleScene/SpellCaster/CasterUIController.h"
#include "Game/BattleScene/SpellCaster/CasterEffectManager.h"

enum class CasterState
{
    Idle,
    EndTurn,
    Passed
};

class CasterController
{
private:
    Event<CasterStat> OnStatUpdate;

protected:
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

    void SetState(CasterState state) { m_CasterState = state; }

    virtual void StartTurn(PentagramData_T data);

    bool TakeDamage(int value); // True if Alive

    CastSpellDetail* CastSpell();

    void EndTurn(bool isPassed = false)
    {
        m_CasterState = isPassed ? CasterState::Passed : CasterState::EndTurn;
    }

    ~CasterController()
    {

    }
};