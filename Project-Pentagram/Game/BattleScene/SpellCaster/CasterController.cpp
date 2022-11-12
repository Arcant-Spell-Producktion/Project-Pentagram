#include "CasterController.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"

CasterController::CasterController(CasterData caster):m_SpellCaster(caster)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    m_CasterObject = scene->CreateObject<CasterObject>(new CasterObject());

    m_CasterUI = new CasterUIController(m_SpellCaster.GetCasterData()->GetPosition());
    m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());
    m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
}

void CasterController::CasterDied()
{
    BattleManager::GetInstance()->EndBattle();
    m_CasterObject->PlayDiedAnim();
}

void CasterController::UpdateCasterUI()
{
    m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());
    m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
}

void CasterController::StartTurn(PentagramData_T data)
{
    if (m_CasterState == CasterState::Passed)
    {
        return;
    }
    m_CasterState = CasterState::Idle;
    m_SpellCaster.SetPentagramData(data);

    UpdateCasterUI();
}

bool CasterController::TakeDamage(int value)
{
    int totalDamage = -value;
    m_SpellCaster.ChangeHealth(totalDamage);

    std::cout << "Caster:" << (int)m_SpellCaster.GetCasterData()->GetPosition()
        << "\tDmg taken: " << value
        << "\tRemained Hp: " << m_SpellCaster.GetHealth() << "\n";
    m_CasterUI->SetHealthText(m_SpellCaster.GetHealth(), m_SpellCaster.GetCasterData()->GetHealth());

    if (m_SpellCaster.GetHealth() <= 0)
    {
        CasterDied();
        return false;
    }
    return true;
}

CastSpellDetail* CasterController::CastSpell()
{

    CastSpellDetail* spell = m_SpellCaster.GetSpellDetail();
    m_SpellCaster.CommitSpell();
    std::cout << "Casted:\n" << *spell << "\n"
        << "\tRemained Mana: " << m_SpellCaster.GetMana() << "\n";
    m_CasterUI->SetManaText(m_SpellCaster.GetMana(), m_SpellCaster.GetCasterData()->GetMana());
    EndTurn();
    return spell;
}