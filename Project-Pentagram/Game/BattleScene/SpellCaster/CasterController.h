#pragma once
#include "SpellCaster.h"
#include "Game/BattleScene/GameObject/CasterUIController.h"

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
    CasterUIController* m_CasterUI = nullptr;
public:

    CasterUIController* GetCasterUI() { return m_CasterUI; }

    void UpdateCasterUI()
    {
        m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());
        m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
    }

    CasterController(CasterData caster):m_SpellCaster(caster)
    {
        m_CasterUI = new CasterUIController(m_SpellCaster.GetCasterData()->GetPosition());
        m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());
        m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
    }

    SpellCaster* GetSpellCaster() {return &m_SpellCaster;}

    CasterState GetState() { return m_CasterState; }
    void SetState(CasterState state) { m_CasterState = state; }

    virtual void StartTurn(PentagramData_T data)
    {
        if (m_CasterState == CasterState::Passed)
        {
            return;
        }
        m_CasterState = CasterState::Idle;
        m_SpellCaster.SetPentagramData(data);

        UpdateCasterUI();
    }

    CastSpellDetail* CastSpell() {

        CastSpellDetail* spell = m_SpellCaster.GetSpellDetail();
        m_SpellCaster.CommitSpell();
        std::cout << "Casted:\n" << *spell << "\n"
            << "\tRemained Mana: "<< m_SpellCaster.GetMana() <<"\n";
        m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
        EndTurn();
        return spell;
    }

    void TakeDamage(int value)
    {
        int totalDamage = -value;
        m_SpellCaster.ChangeHealth(totalDamage);

        std::cout << "Caster:" << (int)m_SpellCaster.GetCasterData()->GetPosition()
            << "\tDmg taken: " << value
            << "\tRemained Hp: " << m_SpellCaster.GetHealth()<< "\n";
        m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());
    }

    void EndTurn(bool isPassed = false)
    {
        m_CasterState = isPassed ? CasterState::Passed : CasterState::EndTurn;
    }

    ~CasterController()
    {

    }
};