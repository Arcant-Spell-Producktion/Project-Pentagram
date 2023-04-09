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

void CasterController::SpinManaWheel()
{
    m_CasterState = CasterState::Spin;

    m_CasterUI.SetWheelValue(m_CasterManager.Data().Stat().ManaWheel);

    if (m_CasterManager.IsManaWheelAllUsed())
    {
        m_CasterManager.ResetManaWheelTracker();
        m_CasterUI.ResetWheel();
    }

    int RandomWheelIndex = m_CasterManager.RandomManaWheelIndex();

    m_CasterUI.SpinWheel(RandomWheelIndex, [this, RandomWheelIndex]()
    {
        m_CasterState = CasterState::Idle;
        m_CasterManager.AddWheelToMana(RandomWheelIndex);
        UpdateCasterUI();
    });
}

void CasterController::StartTurn()
{
    m_CasterUI.SetWheelActive(false);

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
    if (IsImmune())
    {
        totalDamage = 0;
    }
    m_CasterManager.ChangeHealth(totalDamage);

    std::cout << "Caster:" << (int)m_CasterManager.Data().Position()
        << "\tDmg taken: " << value
        << "\tRemained Hp: " << m_CasterManager.GetHealth() << "\n";

    UpdateCasterUI();

    if(totalDamage < 0 ) m_CasterObject->PlayRedFlash();

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
        spell->GetSpellDetail()->GetChannelEffectType() != ChannelEffectEnum::Wait;

    bm->Data.Timeline.AddSpellToTimeline(spell);
    bm->Data.GetCurrentCaster()->GetCasterObject()->PlayChannelAnim();
    bm->Data.GetCurrentCaster()->EndTurn();

    m_CasterManager.CommitSpell();

    std::cout << "Casted:\n" << *spell << "\n"
        << "\tRemained Mana: " << m_CasterManager.GetMana() << "\n";

    UpdateCasterUI();

    EndTurn();
    return spell;
}