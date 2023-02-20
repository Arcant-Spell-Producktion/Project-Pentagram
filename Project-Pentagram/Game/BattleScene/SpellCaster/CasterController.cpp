#include "CasterController.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"

CasterController::CasterController(CasterData caster):m_CasterManager(caster), m_CasterUI(m_CasterManager.Data().Position())
{
    auto scene = GameStateController::GetInstance()->currentScene;
    m_CasterObject = scene->CreateObject<CasterObject>(new CasterObject());

    OnStatUpdate.AddListener([this](CasterStat stat) {m_CasterUI.SetStat(stat); });

    m_EffectManager.OnEffectUpdate.AddListener([this](std::vector<EffectDetail_T> effects) {
        m_CasterUI.UpdateEffectBar(effects);
        });
}

void CasterController::CasterDied()
{
    m_IsAlive = false;
    BattleManager::GetInstance()->EndBattle();
    m_CasterObject->PlayDiedAnim();
}

void CasterController::UpdateCasterUI()
{
    OnStatUpdate.Invoke((m_CasterManager.Data().Stat()));
}

void CasterController::StartTurn()
{
    if (m_CasterState == CasterState::Passed)
    {
        return;
    }

    m_CasterState = CasterState::Idle;
    
    UpdateCasterUI();
}

bool CasterController::IsAlive()
{
    return m_IsAlive;
}

bool CasterController::TakeDamage(int value)
{
    int totalDamage = -value;
    m_CasterManager.ChangeHealth(totalDamage);

    std::cout << "Caster:" << (int)m_CasterManager.Data().Position()
        << "\tDmg taken: " << value
        << "\tRemained Hp: " << m_CasterManager.GetHealth() << "\n";

    UpdateCasterUI();

    m_CasterObject->PlayRedFlash();

    if (m_CasterManager.GetHealth() <= 0)
    {
        CasterDied();
    }

    return IsAlive();
}

CastSpellDetail* CasterController::CastSpell()
{
    auto bm = BattleManager::GetInstance();
    CastSpellDetail* spell = m_CasterManager.GetSpellDetail();

    bool doCompare =
        spell->OriginalSpell->GetChannelEffectType() != ChannelEffectEnum::Wait;

    bm->Data.Timeline.AddSpellToTimeline(spell, doCompare);
    bm->Data.GetCurrentCaster()->GetCasterObject()->PlayChannelAnim();
    bm->Data.GetCurrentCaster()->EndTurn();

    m_CasterManager.CommitSpell();

    std::cout << "Casted:\n" << *spell << "\n"
        << "\tRemained Mana: " << m_CasterManager.GetMana() << "\n";

    UpdateCasterUI();

    EndTurn();
    return spell;
}