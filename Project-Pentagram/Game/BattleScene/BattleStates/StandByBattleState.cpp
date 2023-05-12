#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByBattleState.h"

void StandByBattleState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    battleManager.Data.Pentagram->SetActive(false);

    battleManager.Data.StandbyAllCaster();

}

void StandByBattleState::OnBattleStateUpdate(float dt)
{
    BattleManager& battleManager = BattleManager::GetInstance();

    if (battleManager.Data.IsAllCasterIdle())
    {
        BattleManager::GetInstance().SetBattleState(BattleState::CastState);
    }
}

void StandByBattleState::OnBattleStateOut()
{
    Timer = 0.0f;
    BattleManager& battleManager = BattleManager::GetInstance();
    for (auto caster : battleManager.Data.Casters)
    {
        caster->GetCasterUI()->SetWheelActive(false);
    }
}
