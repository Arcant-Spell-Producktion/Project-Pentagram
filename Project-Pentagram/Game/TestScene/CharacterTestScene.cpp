#include "CharacterTestScene.h"

#include "Game/BattleScene/BattleManager.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/Objects/StageObject.h"
#include "Game/Objects/PauseMenuObject.h"


BattleManager* charTestManager;
PauseMenuObject* test_pauseMenuObject;

void CharacterTestScene::GameSceneLoad()
{
    test_track_t = 0.0f;
    charTestManager = &BattleManager::GetInstance();
    std::cout << "Tutorial Scene : Load Completed\n";
}

void CharacterTestScene::GameSceneInit()
{
    charTestManager->Init(this, RuntimeGameData::GetInstance().Player->Element(),BattleMode::Test);
    std::cout << "Tutorial Scene : Initialize Completed\n";
    charTestManager->StartBattle(BattleMode::Test);

    test_pauseMenuObject = CreateObject(new PauseMenuObject());
    test_pauseMenuObject->SetCurrentGameScene(this);
    test_pauseMenuObject->SetActive(false);
}

void CharacterTestScene::GameSceneUpdate(float dt)
{
    GameScene::GameSceneUpdate(dt);

    if (Input::IsKeyBeginPressed(GLFW_KEY_R))
    {
        SceneManager::LoadScene(GameState::GS_RESTART);
        // If not return will cause memory problem
        return;
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_K))
    {
        charTestManager->EndBattle();
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
    {
        test_pauseMenuObject->ToggleEvent(timeScale);
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_LEFT_ALT) || Input::IsKeyBeginPressed(GLFW_KEY_RIGHT_ALT))
    {
        bool isShow = charTestManager->Data.IsShowCasterDetail();
        charTestManager->Data.SetIsShowCasterDetail(isShow ? false : true);
    }

    charTestManager->GetBattleStates()->OnBattleStateUpdate(scaledDeltaTime);

    if (test_track_t >= 1.0f)
    {
        test_track_t = 0.0f;
    }
    test_track_t += scaledDeltaTime;
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

void CharacterTestScene::GameSceneUnload()
{
    GameScene::GameSceneUnload();
}

void CharacterTestScene::GameSceneFree()
{
    GameScene::GameSceneFree();

    //Free Tutorial Manager
    charTestManager->Free();

    std::cout << "Tutorial Scene : Free Memory Completed\n";
}