#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultTestState.h"

void ResultTestState::OnBattleStateIn()
{
    SceneManager::LoadScene(GameState::GS_RESTART);
}

void ResultTestState::OnBattleStateUpdate(float dt)
{
 
}

void ResultTestState::OnBattleStateOut()
{

}
