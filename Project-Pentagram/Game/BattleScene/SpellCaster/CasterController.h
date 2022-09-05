#pragma once
#include "SpellCaster.h"

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
    SpellCaster m_SpellCaster;
    void (*m_CasterUpdate)(float) = nullptr;
public:
    CasterController(CasterData caster,void (*Update_func)(float) = nullptr):m_SpellCaster(caster), m_CasterUpdate(Update_func){}

    SpellCaster* GetSpellCaster() {return &m_SpellCaster;}

    CasterState GetState() { return m_CasterState; }
    void SetState(CasterState state) { m_CasterState = state; }

    virtual void StartTurn()
    {
        m_CasterState = CasterState::Idle;
        m_SpellCaster.SetPentagramData({ 1,1,1,1,1 });
    }

    virtual void UpdateCaster(float dt)
    {
        if (m_CasterUpdate != nullptr) m_CasterUpdate(dt);
    }

    CastSpellDetail* CastSpell() {

        CastSpellDetail* spell = m_SpellCaster.GetSpellDetail();
        m_SpellCaster.CommitSpell();
        std::cout << "Casted:\n" << *spell->OriginalSpell << "\n"
            << "\tRemained Mana: "<< m_SpellCaster.GetMana() <<"\n";
        EndTurn();
        return spell;
    }

    void EndTurn(bool isPassed = false)
    {
        m_CasterState = isPassed ? CasterState::Passed : CasterState::EndTurn;
    }



    ~CasterController()
    {

    }
};