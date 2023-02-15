#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultBattleState.h"

void ResultBattleState::OnBattleStateIn()
{
    RuntimeGameData* gameData = RuntimeGameData::GetInstance();
    if (gameData->Map->CompleteNode())
    {
        SceneManager::LoadScene(GameState::GS_MENU_SCENE);
    }
    else
    {
        SceneManager::LoadScene(GameState::GS_MAP_SCENE);
    }
}

void ResultBattleState::OnBattleStateUpdate(float dt)
{

}

void ResultBattleState::OnBattleStateOut()
{
}
