#include "Engine/GameStateController.h"
#include "CasterUIController.h"

CasterUIController::CasterUIController(CasterPosition position)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int pos = (int)position - 1;
    m_StatUI = scene->CreateObject(new CasterDetailUI(pos));
    m_DetailBox = scene->CreateObject(new SpellDetailUI(pos));
    m_Roulette = scene->CreateObject(new ManaRouletteUI(pos));
    m_Roulette->SetActive(false);

}

void CasterUIController::SetStat(CasterStat stat)
{
    m_StatUI->SetHealthText(stat.CurrentHealth,stat.MaxHealth);
    m_StatUI->SetManaText(stat.CurrentMana, stat.MaxMana);
    m_Roulette->SetActive(false);

}


void CasterUIController::SetDetail(CastSpellDetail* spell, bool isMainData, glm::vec3 IconPos)
{
    m_DetailBox->SetDetail(spell, isMainData);
}

void CasterUIController::UpdateEffectBar(std::vector<EffectDetail_T> effects)
{
    m_StatUI->SetEffectBar(effects);
}

void CasterUIController::SpinWheel(int n, std::function<void()> callback)
{
    m_Roulette->SetActive(true);
    m_Roulette->SetSpinResult(n, callback);
}
