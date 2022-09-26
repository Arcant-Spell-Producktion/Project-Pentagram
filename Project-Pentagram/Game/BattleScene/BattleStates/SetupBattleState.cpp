#pragma once
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SetupBattleState.h"

void SetupBattleState::OnBattleStateIn()
{
    BattleSceneData* currentBattleData = BattleManager::GetInstance()->GetData();
    currentBattleData->AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));
    currentBattleData->AddCaster(new PlayerController({ Element::Fire,CasterPosition::CasterB,100,10 }));
}

void SetupBattleState::OnBattleStateUpdate(float dt)
{
}

void SetupBattleState::OnBattleStateOut()
{
}
