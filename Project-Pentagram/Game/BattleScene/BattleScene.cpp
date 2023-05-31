#include "BattleScene.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/BattleScene/BattleManager.h"
#include "Game/Objects/StageObject.h"
#include "Game/Objects/PauseMenuObject.h"

float track_t = 0.0f;

BattleManager* battleManager;
PauseMenuObject* pauseMenuObject;

void BattleScene::GameSceneLoad()
{
    track_t = 0.0f;
    battleManager = &BattleManager::GetInstance();
    std::cout << "Battle Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    battleManager->Init(this, RuntimeGameData::GetInstance().Map->GetNextNode()->GetEnemyData().Element());
    std::cout << "Battle Scene : Initialize Completed\n";
    battleManager->StartBattle();

    playerAidUI = CreateObject(new PlayerAidUI());
    playerAidUI->SetActive(false);

    pauseMenuObject = CreateObject(new PauseMenuObject());
    pauseMenuObject->SetCurrentGameScene(this);
    pauseMenuObject->SetActive(false);

    battleManager->Data.Shortcut->GetPauseButton()->onClick.AddListener([this](Button* button)
        {
            pauseMenuObject->ToggleEvent(timeScale);
        });

    battleManager->Data.Shortcut->GetHelpButton()->onClick.AddListener([this](Button* button)
        {
            playerAidUI->ToggleEvent(timeScale);
        });
}

void BattleScene::GameSceneUpdate(float dt)
{
    GameScene::GameSceneUpdate(dt);

    if (Input::IsKeyBeginPressed(GLFW_KEY_R))
    {
        SceneManager::LoadScene(GameState::GS_RESTART);
        // If not return will cause memory problem
        return;
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_L))
    {
        battleManager->Data.GetCaster(CasterPosition::CasterA)->TakeDamage(999);
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_K))
    {
        battleManager->EndBattle();
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
    {
        if(!playerAidUI->IsActive())
            pauseMenuObject->ToggleEvent(timeScale);
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_F1))
    {
        if (!pauseMenuObject->IsActive())
            playerAidUI->ToggleEvent(timeScale);
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_LEFT_ALT) || Input::IsKeyBeginPressed(GLFW_KEY_RIGHT_ALT))
    {
        bool isShow = battleManager->Data.IsShowCasterDetail();
        battleManager->Data.SetIsShowCasterDetail(isShow ? false : true);
    }

    battleManager->GetBattleStates()->OnBattleStateUpdate(scaledDeltaTime);

    if (track_t >= 1.0f)
    {
        track_t = 0.0f;
    }
    track_t += scaledDeltaTime;
    // Update GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        GameObject*& curObj = objectsList[idx];

        curObj->OnUpdate(scaledDeltaTime);
        if (curObj->IsAnimationObject())
        {
            curObj->UpdateAnimation(scaledDeltaTime);
        }
    }

    // Update UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        UIObject*& curObj = uiObjectsList[idx];

        if (curObj->IsAnimationObject())
        {
            curObj->UpdateAnimation(scaledDeltaTime);
        }

        if (!curObj->IsActive()) { continue; }

        curObj->OnUpdate(scaledDeltaTime);
    }
}

void BattleScene::GameSceneUnload()
{
    GameScene::GameSceneUnload();
}

void BattleScene::GameSceneFree()
{
    GameScene::GameSceneFree();

    //Free Battle Manager
    battleManager->Free();

    std::cout << "Battle Scene : Free Memory Completed\n";
}