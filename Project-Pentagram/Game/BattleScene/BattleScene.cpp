#include "BattleScene.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"

#include "Game/GameData/RuntimeGameData.h"
#include "SpellCaster/PlayerController.h"
#include "Game/BattleScene/BattleManager.h"

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
    battleManager->Init();

    ParticleProperty particleProp;
    particleProp.colorBegin = { 1.0f, 0.0f, 0.0f, 1.0f };
    particleProp.colorEnd = { 1.0f, 0.5f, 0.0f, 0.0f };
    particleProp.sizeBegin = particleProp.sizeEnd = 10.0f;
    particleProp.velocityVariation = { 600.0f, 600.0f };
    particleProp.velocity = { 0.0f, 300.0f };
    ParticleSystem* particle = CreateParticle(particleProp);

    GameObject* obj = CreateGameObject("Player", 2, { 5,8 });
    obj->SetIsAnimationObject(true);
    obj->scale = { 320.0f, 320.0f, 1.0f };
    obj->SetTexture("Sprites/Character/Player/character_player_fire.png");
    obj->position.x -= 700.0f;
    obj->SetChildRenderBack(particle);

    GameObject* obj2 = CreateGameObject("Floor");
    obj2->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    obj2->scale = { 1920.0f, 500.0f, 1.0f };
    obj2->position.y = -400.0f;

    GameObject* obj3 = CreateGameObject("Minion", 1, { 5 });
    obj3->SetIsAnimationObject(true);
    obj3->scale = { -320.0f, 320.0f, 1.0f };
    obj3->SetTexture("Sprites/Character/Minion/character_minion_water.png");
    obj3->position.x += 700.0f;

    battleManager->GetData()->pentragramController = new PentragramController();
    objectsList.push_back(battleManager->GetData()->pentragramController);

    
    std::cout << "Battle Scene : Initialize Completed\n";

    battleManager->StartBattle();
}

void BattleScene::GameSceneUpdate(float dt)
{
    UpdateButtonEvents();

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

        if (curObj->name == "INFO_Text" && track_t >= 1.0f)
        {
            dynamic_cast<TextObject*>(curObj)->text = "FPS : " + std::to_string(int(1.0f / dt)) + "\n" +
                "GameObject : " + std::to_string(objectsList.size()) + "\n" +
                "UIObject : " + std::to_string(uiObjectsList.size());
        }
        else if (curObj->name == "BigUI_1")
        {
            if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
            {
                timeScale = timeScale == 0.0f ? 1.0f : 0.0f;
                soundSystem->SetPauseAll(soundSystem->isAllPaused() ? false : true);
                curObj->SetActive(curObj->IsActive() ? false : true);
            }
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