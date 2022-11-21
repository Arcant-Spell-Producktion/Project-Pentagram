#include "CasterController.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"

CasterController::CasterController(CasterData caster):m_CasterManager(caster), m_CasterUI(m_CasterManager.Data().Position())
{
    auto scene = GameStateController::GetInstance()->currentScene;
    m_CasterObject = scene->CreateObject<CasterObject>(new CasterObject());

    OnStatUpdate.AddListenner([this](CasterStat stat) {m_CasterUI.SetStat(stat); });
}

void CasterController::CasterDied()
{
    BattleManager::GetInstance()->EndBattle();
    m_CasterObject->PlayDiedAnim();
}

void CasterController::UpdateCasterUI()
{
    OnStatUpdate.Invoke((m_CasterManager.Data().Stat()));
}

void CasterController::StartTurn(PentagramData_T data)
{
    if (m_CasterState == CasterState::Passed)
    {
        return;
    }
    m_CasterState = CasterState::Idle;
    m_CasterManager.SetPentagramData(data);

    UpdateCasterUI();
}

bool CasterController::TakeDamage(int value)
{
    int totalDamage = -value;
    m_CasterManager.ChangeHealth(totalDamage);

    std::cout << "Caster:" << (int)m_CasterManager.Data().Position()
        << "\tDmg taken: " << value
        << "\tRemained Hp: " << m_CasterManager.GetHealth() << "\n";

    UpdateCasterUI();

    if (m_CasterManager.GetHealth() <= 0)
    {
        CasterDied();
        return false;
    }
    return true;
}

CastSpellDetail* CasterController::CastSpell()
{

    CastSpellDetail* spell = m_CasterManager.GetSpellDetail();
    m_CasterManager.CommitSpell();
    std::cout << "Casted:\n" << *spell << "\n"
        << "\tRemained Mana: " << m_CasterManager.GetMana() << "\n";

    UpdateCasterUI();

    EndTurn();
    return spell;
}