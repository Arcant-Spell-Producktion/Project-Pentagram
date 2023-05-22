#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultBattleState.h"

void ResultBattleState::OnBattleStateIn()
{
    m_Timer = m_WaitTime;
    BattleManager& battleManager = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    CasterController* player = battleManager.Data.GetCaster(CasterPosition::CasterA);

    if (!player->IsAlive())
    {
        player->CasterDied();
        battleManager.Data.Stage->FadeToBlack();
        m_Timer = 10.0f;
    }
}

void ResultBattleState::OnBattleStateUpdate(float dt)
{
    if (m_Timer < 0.0f)
    {
        BattleManager& battleManager = BattleManager::GetInstance();
        RuntimeGameData& gameData = RuntimeGameData::GetInstance();
        CasterController* player = battleManager.Data.GetCaster(CasterPosition::CasterA);

        if (!player->IsAlive())
        {
            SceneManager::LoadScene(GameState::GS_MENU_SCENE);
            gameData.DeleteSave();
        }
        else
        {
            if (gameData.Map->CompleteNode())
            {
                std::cout << "!!!!!!!!XXXX\t\tSaving at " << gameData.Map->GetCurrentChapter() << std::endl;

                if(gameData.Map->GetCurrentChapter() == Element::Corrupt)
                {
                    gameData.DeleteSave();
                    SceneManager::LoadScene(GameState::GS_MENU_SCENE);
                    return;
                }
                else
                {
                    gameData.Player->LevelUp();
                    SceneManager::LoadScene(GameState::GS_MAP_SCENE);
                }
                
            }
            else
            {
                gameData.Player->Stat().CurrentHealth = player->GetCasterManager()->Data().Stat().CurrentHealth;

                SceneManager::LoadScene(GameState::GS_BATTLE_SCENE);
            }

            gameData.Map->IsAtMap = false;
            gameData.SaveGameData();
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
