#pragma once
#include "CasterSpellManager.h"
#include "Game/BattleScene/GameObject/CasterUIController.h"
#include "Game/BattleScene/SpellCaster/CasterEffectManager.h"

enum class CasterState
{
    Idle,
    Chant,
    Cast,
    EndTurn,
    Passed
};

class CasterController
{
protected:
    CasterState m_CasterState = CasterState::Idle;
    CasterSpellManager m_SpellCaster;
    CasterEffectManager m_EffectManager;
    CasterUIController* m_CasterUI;
public:

    CasterController(CasterData caster);

    void UpdateCasterUI();
   
    CasterUIController* GetCasterUI() { return m_CasterUI; }

    CasterSpellManager* GetSpellManager() {return &m_SpellCaster;}
    
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