#pragma once
#include "Engine/SceneManager.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/BattleScene/SpellCaster/PlayerController.h"
#include "Game/GameData/RuntimeGameData.h"
#include "ResultBattleState.h"

void ResultBattleState::OnBattleStateIn()
{
    BattleManager& battleManager = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    PlayerController* player = dynamic_cast<PlayerController*>(battleManager.Data.GetCaster(CasterPosition::CasterA));

    GameScene* scene = GameStateController::GetInstance().currentScene;
    Camera* camera = scene->GetCamera();

    m_IsAlive = player->IsAlive();
    if (!m_IsAlive)
    {
        player->GetCasterObject()->SetIsAnimationObject(false);
        battleManager.Data.Stage->FadeToBlack();
        battleManager.Data.HideCasterUI();
        battleManager.Data.Timeline.UI->SetActive(false);

        battleManager.Data.GameOverUI->ButtonA->onClick = [this](Button* button)
        {
            SceneManager::LoadScene(GameState::GS_MENU_SCENE);
        };

        battleManager.Data.GameOverUI->ButtonB->onClick = [this](Button* button)
        {
            SceneManager::LoadScene(GameState::GS_QUIT);
        };

        gameData.DeleteSave();
    }
}

void ResultBattleState::OnBattleStateUpdate(float dt)
{

    BattleManager& battleManager = BattleManager::GetInstance();
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    PlayerController* player = dynamic_cast<PlayerController*>(battleManager.Data.GetCaster(CasterPosition::CasterA));

    GameScene* scene = GameStateController::GetInstance().currentScene;
    Camera* camera = scene->GetCamera();

    if (m_Timer >= m_WaitTime)
    {

        if (m_IsAlive)
        {
            if (gameData.Map->CompleteNode())
            {
                std::cout << "!!!!!!!!XXXX\t\tSaving at " << gameData.Map->GetCurrentChapter() << std::endl;

                if (gameData.Map->GetCurrentChapter() == Element::Corrupt)
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

    }
    else
    {
        m_Timer += dt;

        if (m_Timer >= m_WaitTime)
        {
            if (!m_IsAlive)
            {
                player->GetCasterObject()->PlayDiedAnim();
                player->GetCasterObject()->SetIsAnimationObject(true);
                player->GetCasterObject()->SetAnimationPlayTime(0.15f);

                battleManager.Data.GameOverUI->SetActive(true);
            }

            m_Timer = m_WaitTime;
        }

        if (!m_IsAlive)
        {
            GameScene* scene = GameStateController::GetInstance().currentScene;
            Camera* camera = scene->GetCamera();
            //cam pos -150 -50 ,zoom 1.7f

            float camX = -235.0f * (m_Timer / m_WaitTime);
            float camY = -100.0f * (m_Timer / m_WaitTime);

            float camZoom = 1.0f + ((m_Timer / m_WaitTime) * 0.5f);

            camera->SetZoom(camZoom);
            camera->position.x = camX;
            camera->position.y = camY;
        }
    }
}

void ResultBattleState::OnBattleStateOut()
{
    m_Timer = 0;
}
