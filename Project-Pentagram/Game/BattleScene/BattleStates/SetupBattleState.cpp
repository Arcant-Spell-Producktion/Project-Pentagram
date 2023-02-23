#pragma once
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/BattleScene/SpellCaster/EnemyController.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"


#include "SetupBattleState.h"

void SetupBattleState::OnBattleStateIn()
{
    BattleManager* bm = BattleManager::GetInstance();
    RuntimeGameData* gameData = RuntimeGameData::GetInstance();
    NodeData* currentNode = gameData->Map->GetNextNode();
    std::cout << "DEBUG ENEMY ELEMENT: " << (int)currentNode->GetEnemyData().Element() << "\n";

    bm->Data.AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));

    bm->Data.AddCaster(new EnemyController( currentNode->GetEnemyData()));
}

void SetupBattleState::OnBattleStateUpdate(float dt)
{
}

void SetupBattleState::OnBattleStateOut()
{
}
