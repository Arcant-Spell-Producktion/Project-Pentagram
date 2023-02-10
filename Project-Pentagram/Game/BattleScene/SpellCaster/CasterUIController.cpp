#include "Engine/GameStateController.h"
#include "CasterUIController.h"

CasterUIController::CasterUIController(CasterPosition position)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int pos = (int)position - 1;
    m_StatUI = scene->CreateObject(new CasterDetailUI(pos));
    m_DetailBox = scene->CreateObject(new SpellDetailUI(pos));

}

void CasterUIController::SetStat(CasterStat stat)
{
    m_StatUI->SetHealthText(stat.CurrentHealth,stat.MaxHealth);
    m_StatUI->SetManaText(stat.CurrentMana, stat.ManaWheel[stat.CurrentManaWheel]);
}


void CasterUIController::SetDetail(CastSpellDetail* spell, bool isMainData, glm::vec3 IconPos)
{
    m_DetailBox->SetDetail(spell, isMainData);
}

void CasterUIController::UpdateEffectBar(std::vector<EffectDetail_T> effects)
{
    m_StatUI->SetEffectBar(effects);
}
