#include "BattleScene.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"

#include "Game/GameData/RuntimeGameData.h"
#include "SpellCaster/PlayerController.h"
#include "Game/BattleScene/BattleManager.h"
#include <Game/Objects/StageObject.h>

float track_t = 0.0f;

BattleManager* battleManager;

void BattleScene::GameSceneLoad()
{
    track_t = 0.0f;
    battleManager = BattleManager::GetInstance();
    std::cout << "Battle Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    objectsList.push_back(new StageObject(Element::Water));

    battleManager->Init();

    battleManager->Data.Pentagram = CreateObject<PentragramController>(new PentragramController());
    battleManager->Data.Timeline.UI = CreateObject<TimelineController>(new TimelineController());
    
    std::cout << "Battle Scene : Initialize Completed\n";

    battleManager->StartBattle();
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

    battleManager->GetBattleStates()->OnBattleStateUpdate(dt);

    if (track_t >= 1.0f)
    {
        track_t = 0.0f;
    }
    track_t += dt;
    // Update GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        GameObject*& curObj = objectsList[idx];

        curObj->OnUpdate(dt);
        if (curObj->IsAnimationObject())
        {
            curObj->UpdateAnimation(dt);
        }
        if (curObj->GetTag() == GameObjectTag::PARTICLE && Input::IsKeyBeginPressed(GLFW_KEY_3))
        {
            curObj->SetActive(curObj->IsActive() ? false : true);
        }
    }

    // Update UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        UIObject*& curObj = uiObjectsList[idx];

        if (curObj->IsAnimationObject())
        {
            curObj->UpdateAnimation(dt);
        }

        if (!curObj->IsActive()) { continue; }

        curObj->OnUpdate(dt);
    }
}

void BattleScene::GameSceneUnload()
{
    //Free Battle Manager
    battleManager->Free();
    GameScene::GameSceneUnload();
}

void BattleScene::GameSceneFree()
{
    // Free GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        delete objectsList[idx];
    }
    // Free UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        delete uiObjectsList[idx];
    }

    std::cout << "Battle Scene : Free Memory Completed\n";
}