#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
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
            SceneManager::LoadScene(GameState::GS_TUTORIAL_SELECT_SCENE);
        }
        else
        {
            SceneManager::LoadScene(GameState::GS_MENU_SCENE);
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
