#pragma once
#include "Engine/SceneManager.h"

#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "StandByTutorialState.h"

#include "Game/BattleScene/BattleManager.h"

void StandByTutorialState::OnBattleStateIn()
{
    BattleManager* battleManager = BattleManager::GetInstance();
    for (auto caster : battleManager->Data.Casters)
    {
        caster->UpdateCasterUI();
        caster->GetCasterUI()->SetWheelActive(false);
    }
    BattleManager::GetInstance()->SetBattleState(BattleState::CastState);

}

void StandByTutorialState::OnBattleStateUpdate(float dt)
{
    
}

void StandByTutorialState::OnBattleStateOut()
{
    Timer = 0.0f;
}
