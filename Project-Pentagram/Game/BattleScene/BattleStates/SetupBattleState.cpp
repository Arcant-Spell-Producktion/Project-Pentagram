#pragma once
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SetupBattleState.h"

void SetupBattleState::OnBattleStateIn(BattleSceneData* currentBattleData)
{
    currentBattleData->AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));
    currentBattleData->AddCaster(new CasterController({ Element::Debug,CasterPosition::CasterB,1,1 }));
}
