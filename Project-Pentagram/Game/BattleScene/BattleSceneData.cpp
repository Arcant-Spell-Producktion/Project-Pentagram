#include "BattleSceneData.h"

CasterController* BattleSceneData::GetCaster(CasterPosition position)
{
    CasterController* caster = nullptr;
    for (auto c : Casters)
    {
        if (c->GetSpellCaster()->GetCasterData()->GetPosition() == position)
        {
            caster = c;
            break;
        }
    }
    return caster;
}

void BattleSceneData::StandbyAllCaster()
{
    for (auto caster : Casters)
    {
        caster->SetState(CasterState::Idle);
        caster->GetSpellCaster()->ResetMana();
        caster->UpdateCasterUI();
    }
}
