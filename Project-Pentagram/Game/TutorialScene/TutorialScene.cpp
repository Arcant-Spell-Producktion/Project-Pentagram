#include "TutorialScene.h"

#include "Game/BattleScene/BattleManager.h"
#include "Game/TutorialScene/TutorialStates/TutorialStateModel.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/Objects/StageObject.h"
#include "Game/Objects/PauseMenuObject.h"


BattleManager* tutorialManager;
PauseMenuObject* tur_pauseMenuObject;

void TutorialScene::GameSceneLoad()
{
    tur_track_t = 0.0f;
    tutorialManager = BattleManager::GetInstance();
    std::cout << "Tutorial Scene : Load Completed\n";
}

void TutorialScene::GameSceneInit()
{
    objectsList.push_back(new StageObject(Element::Water));

    tutorialManager->Init(this,true);
    std::cout << "Tutorial Scene : Initialize Completed\n";
    tutorialManager->StartBattle(true);

    tur_pauseMenuObject = CreateObject(new PauseMenuObject());
    tur_pauseMenuObject->SetCurrentGameScene(this);
    tur_pauseMenuObject->SetActive(false);
}

void TutorialScene::GameSceneUpdate(float dt)
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
        tutorialManager->EndBattle();
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
    {
        tur_pauseMenuObject->SetActive(tur_pauseMenuObject->IsActive() ? false : true);
        timeScale = (timeScale == 1.0f ? 0.0f : 1.0f);
    }
    else if (Input::IsKeyBeginPressed(GLFW_KEY_LEFT_ALT) || Input::IsKeyBeginPressed(GLFW_KEY_RIGHT_ALT))
    {
        bool isShow = tutorialManager->Data.IsShowCasterDetail();
        tutorialManager->Data.SetIsShowCasterDetail(isShow ? false : true);
    }

    tutorialManager->GetBattleStates()->OnBattleStateUpdate(scaledDeltaTime);

    if (tur_track_t >= 1.0f)
    {
        tur_track_t = 0.0f;
    }
    tur_track_t += scaledDeltaTime;
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

void TutorialScene::GameSceneUnload()
{
    GameScene::GameSceneUnload();
}

void TutorialScene::GameSceneFree()
{
    GameScene::GameSceneFree();

    //Free Tutorial Manager
    tutorialManager->Free();

    std::cout << "Tutorial Scene : Free Memory Completed\n";
}