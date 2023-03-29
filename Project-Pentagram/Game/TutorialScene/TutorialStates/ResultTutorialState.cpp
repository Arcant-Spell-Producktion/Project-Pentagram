#pragma once
#include "Engine/SceneManager.h"
#include "Game/TutorialScene/TutorialManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultTutorialState.h"

void ResultTutorialState::OnBattleStateIn()
{
    m_Timer = m_WaitTime;
}

void ResultTutorialState::OnBattleStateUpdate(float dt)
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

void ResultTutorialState::OnBattleStateOut()
{
    m_Timer = 0;
}
