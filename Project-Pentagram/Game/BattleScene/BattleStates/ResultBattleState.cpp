#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultBattleState.h"

void ResultBattleState::OnBattleStateIn()
{
    m_Timer = m_WaitTime;
 
}

void ResultBattleState::OnBattleStateUpdate(float dt)
{
    if (m_Timer < 0.0f)
    {
        RuntimeGameData* gameData = RuntimeGameData::GetInstance();
        if (gameData->Player->Stat().CurrentHealth <= 0)
        {
            SceneManager::LoadScene(GameState::GS_MENU_SCENE);
            gameData->DeleteSave();
        }
        else
        {
            if (gameData->Map->CompleteNode())
            {
                gameData->Player->LevelUp();
                SceneManager::LoadScene(GameState::GS_MENU_SCENE);
            }
            //SceneManager::LoadScene(GameState::GS_MAP_SCENE);
            else
            {
                SceneManager::LoadScene(GameState::GS_BATTLE_SCENE);
            }
            gameData->SaveGameData();
        }

    }else
    {
        m_Timer -= dt;
    }
}

void ResultBattleState::OnBattleStateOut()
{
    m_Timer = 0;
}
