#include "BattleSceneData.h"

CasterController* BattleSceneData::GetCaster(CasterPosition position)
{
    CasterController* caster = nullptr;
    for (auto c : Casters)
    {
        if (c->GetSpellManager()->GetCasterData()->GetPosition() == position)
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
        caster->GetSpellManager()->ResetMana();
        caster->GetSpellManager()->ResetTimeDebuff();
        caster->GetEffectManager()->ResolveEffect(EffectResolveType::OnStartTurn, 1, caster);
        caster->UpdateCasterUI();
    }
}
