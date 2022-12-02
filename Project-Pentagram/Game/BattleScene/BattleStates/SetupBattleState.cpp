#pragma once
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SetupBattleState.h"

void SetupBattleState::OnBattleStateIn()
{
    BattleManager* bm = BattleManager::GetInstance();
    bm->Data.AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));
    bm->Data.AddCaster(new PlayerController({ {450,15}, Element::Water,CasterPosition::CasterB }));
}

void SetupBattleState::OnBattleStateUpdate(float dt)
{
}

void SetupBattleState::OnBattleStateOut()
{
}
