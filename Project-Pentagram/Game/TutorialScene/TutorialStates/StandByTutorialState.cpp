#pragma once
#include "Engine/SceneManager.h"

#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByTutorialState.h"

#include "Game/BattleScene/BattleManager.h"

void StandByTutorialState::OnBattleStateIn()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(false);

    battleManager->Data.StandbyAllCaster();

    Timer = MaxTime;
}

void StandByTutorialState::OnBattleStateUpdate(float dt)
{
    BattleManager* battleManager = BattleManager::GetInstance();

    if (battleManager->Data.IsAllCasterIdle() && Timer > 0)
    {
        Timer -= dt;
        if (Timer < 0.0f)
        {
            BattleManager::GetInstance()->SetBattleState(BattleState::CastState);
        }
    }
}

void StandByTutorialState::OnBattleStateOut()
{
    Timer = 0.0f;
    BattleManager* battleManager = BattleManager::GetInstance();
    battleManager->Data.Pentagram->SetActive(true);
    for (auto caster : battleManager->Data.Casters)
    {
        caster->GetCasterUI()->SetWheelActive(false);
    }
}
