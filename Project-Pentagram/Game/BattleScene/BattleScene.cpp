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

    battleManager->Init(this);
    
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
    GameScene::GameSceneUnload();
}

void BattleScene::GameSceneFree()
{
    GameScene::GameSceneFree();

    //Free Battle Manager
    battleManager->Free();

    std::cout << "Battle Scene : Free Memory Completed\n";
}