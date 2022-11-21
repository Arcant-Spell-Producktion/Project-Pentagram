#include "Engine/GameStateController.h"
#include "CasterUIController.h"

CasterUIController::CasterUIController(CasterPosition position)
{
    auto scene = GameStateController::GetInstance()->currentScene;
    int flip = (int)position == 0 ? 1 : -1;
    m_StatUI = scene->CreateObject(new CasterDetailUI((int)position - 1));
    m_DetailBox = new SpellDetailUI(flip);
}

void CasterUIController::SetStat(CasterStat stat)
{
    m_StatUI->SetHealthText(stat.CurrentHealth,stat.MaxHealth);
    m_StatUI->SetManaText(stat.CurrentMana, stat.MaxMana);
}

void CasterUIController::SetDetail(CastSpellDetail* detail)
{
    m_DetailBox->SetDetail(detail);
}
