#include "Engine/GameStateController.h"
#include "CasterUIController.h"

#include "Game/BattleScene/BattleManager.h"

CasterUIController::CasterUIController(CasterPosition position)
{
    BattleManager::GetInstance().Data.Timeline.UI->OnTimetrackExpand.AddListener([this](bool doExpand)
        {
            m_DetailBox->SetActive(doExpand ? false : m_IsShowDetailBox);
        });

    auto scene = GameStateController::GetInstance().currentScene;
    int pos = (int)position - 1;
    m_StatUI = scene->CreateObject(new CasterDetailUI(pos));
    m_DetailBox = scene->CreateObject(new SpellDetailUI(pos));
    m_DetailBox->SetActive(false);
    m_IsShowDetailBox = true;
    m_Roulette = scene->CreateObject(new ManaRouletteUI(pos));
    m_Roulette->SetActive(false);
}

void CasterUIController::SetStat(CasterStat stat)
{
    m_StatUI->SetHealthText(stat.CurrentHealth,stat.MaxHealth);
    m_StatUI->SetManaText(stat.CurrentMana, stat.MaxMana);
}

void CasterUIController::SetIsShowDetail(bool active)
{
    if (m_Roulette->IsActive() || BattleManager::GetInstance().Data.Timeline.UI->IsTimelineExpand()) { return; }

    m_DetailBox->SetActive(active);
    m_IsShowDetailBox = active;
}
bool CasterUIController::IsShowDetail()
{
    return m_DetailBox->IsActive();
}

void CasterUIController::SetDetail(CastSpellDetail* spell, bool isMainData, glm::vec3 IconPos)
{
    m_DetailBox->SetDetail(spell, isMainData);
}

void CasterUIController::UpdateEffectBar(std::vector<EffectDetail_T> effects)
{
    m_StatUI->SetEffectBar(effects);
}

void CasterUIController::SetWheelValue(std::array<int, 6> numbers)
{
    m_Roulette->SetRouletteNumbers(numbers);
}

void CasterUIController::SetWheelActive(bool isActive)
{
    m_Roulette->SetActive(isActive);
    if (isActive)
    {
        m_DetailBox->SetActive(false);
    }
    else
    {
        m_DetailBox->SetActive(m_IsShowDetailBox);
    }
};

bool CasterUIController::IsWheelActive() const
{
    return m_Roulette->IsActive();
}

void CasterUIController::SpinWheel(int n, std::function<void()> callback)
{
    this->SetWheelActive(true);
    m_Roulette->SetSpinResult(n, callback);
}

void CasterUIController::ResetWheel()
{
    m_Roulette->ResetRoulette();
}

void CasterUIController::SetActive(bool isActive)
{
    m_StatUI->SetActive(isActive);
    m_Roulette->SetActive(isActive);
    m_DetailBox->SetActive(isActive);
}
