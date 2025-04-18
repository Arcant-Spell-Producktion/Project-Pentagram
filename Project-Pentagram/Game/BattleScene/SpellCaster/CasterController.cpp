#include "CasterController.h"
#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"

CasterController::CasterController(CasterData caster): m_CasterManager(caster),m_CasterUI(m_CasterManager.Data().Position())
{
    auto scene = GameStateController::GetInstance().currentScene;
    m_CasterObject = scene->CreateObject<CasterObject>(new CasterObject());

    OnStatUpdate.AddListener([this](CasterStat stat) {m_CasterUI.SetStat(stat); });

    m_EffectManager.OnEffectUpdate.AddListener([this](std::vector<EffectDetail_T> effects) {
        m_CasterUI.UpdateEffectBar(effects);
        });

    m_EffectManager.OnEffectApply = [this](SpellEffectEnum type) {m_CasterObject->PlayEffect(type); };
    m_EffectManager.OnEffectResolve = [this](SpellEffectEnum type) {m_CasterObject->PlayEffect(type); };
    m_EffectManager.OnEffectReset = [this](SpellEffectEnum type) {m_CasterObject->StopEffect(type); };

    // If Caster is Enemy -> Turn off DetailBox
    if (caster.Position() == CasterPosition::CasterB) { m_CasterUI.SetIsShowDetail(false); }
}

void CasterController::CasterDied()
{
    m_IsAlive = false;
    BattleManager::GetInstance().EndBattle();
    m_CasterObject->PlayDiedAnim();
}

void CasterController::UpdateCasterUI()
{
    OnStatUpdate.Invoke((m_CasterManager.Data().Stat()));
}

void CasterController::SpinManaWheel(int forceValue)
{
    m_CasterState = CasterState::Spin;

    m_CasterUI.SetWheelValue(m_CasterManager.Data().Stat().ManaWheel);

    if (m_CasterManager.IsManaWheelAllUsed())
    {
        m_CasterManager.ResetManaWheelTracker();
        m_CasterUI.ResetWheel();
    }

    int RandomWheelIndex = forceValue < 0 ? m_CasterManager.RandomManaWheelIndex() : forceValue - 1;

    m_CasterUI.SpinWheel(RandomWheelIndex, [this, RandomWheelIndex]()
    {
        m_CasterState = CasterState::Idle;
        m_CasterManager.AddWheelToMana(RandomWheelIndex);
        UpdateCasterUI();
    });
}

void CasterController::StartRound()
{
    GetEffectManager()->ResolveEffect(EffectResolveType::OnStartTurn, 1, this);
    UpdateCasterUI();
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

void CasterController::EndCastPhase()
{
    GetCasterManager()->ResetBuff();
    GetCasterManager()->ResetDebuff();
    GetEffectManager()->OnCastPhaseEnd();
    UpdateCasterUI();
}

void CasterController::EndRound()
{
    GetEffectManager()->OnEndRound();
    UpdateCasterUI();
}

bool CasterController::SetHp(int value)
{
    m_CasterManager.SetHealth(value);

    if (m_CasterManager.GetHealth() <= 0)
    {
        CasterDied();
    }

    UpdateCasterUI();

    return IsAlive();
}

void CasterController::SetMana(int value)
{
    m_CasterManager.Data().Stat().MaxMana = value;
    m_CasterManager.Data().Stat().CurrentMana = m_CasterManager.Data().Stat().MaxMana;

    UpdateCasterUI();
}

void CasterController::Heal(int value)
{
    m_CasterManager.ChangeHealth(value);

    std::cout << "Caster:" << (int)m_CasterManager.Data().Position()
        << "\tHealed: " << value
        << "\tRemained Hp: " << m_CasterManager.GetHealth() << "\n";

    if (value > 0) m_CasterObject->PlayGreenFlash();

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
    BattleManager& bm = BattleManager::GetInstance();
    CastSpellDetail* spell = m_CasterManager.GetSpellDetail();

    bool doCompare =
        spell->GetSpellDetail()->GetChannelEffectType() != ChannelEffectEnum::Wait;

    bm.Data.Timeline.AddSpellToTimeline(spell);
    bm.Data.GetCurrentCaster()->GetCasterObject()->PlayChannelAnim();
    bm.Data.GetCurrentCaster()->EndTurn();

    m_CasterManager.CommitSpell();

    std::cout << "Casted:\n" << *spell << "\n"
        << "\tRemained Mana: " << m_CasterManager.GetMana() << "\n";

    UpdateCasterUI();

    EndTurn();
    return spell;
}