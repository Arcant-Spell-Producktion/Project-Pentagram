#include "BattleSceneData.h"

CasterController* BattleSceneData::GetCaster(CasterPosition position)
{
    CasterController* caster = nullptr;
    for (auto c : Casters)
    {
        if (c->GetCasterManager()->Data().Position() == position)
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
        caster->SpinManaWheel();
    }
}

bool BattleSceneData::IsAllCasterIdle()
{
    bool isAllIdle = true;

    for (auto caster : Casters)
    {
        if (caster->GetState() != CasterState::Idle) isAllIdle = false;
    }

    return isAllIdle;
}

void BattleSceneData::StartRound()
{
    for (auto caster : Casters)
    {
        caster->StartRound();
    }
}

void BattleSceneData::EndCastPhase()
{
    for (auto caster : Casters)
    {
        caster->EndCastPhase();
    }
}

void BattleSceneData::EndRound()
{
    for (auto caster : Casters)
    {
        caster->EndRound();
    }
}