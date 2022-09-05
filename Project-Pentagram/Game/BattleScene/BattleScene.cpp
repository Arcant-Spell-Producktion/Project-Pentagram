#include "BattleScene.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SpellCaster/PlayerController.h"


void BattleScene::CastStateUpdate(float dt)
{
    CasterController* currentController = m_BattleManager->GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle
    
    currentController->UpdateCaster(dt);

    if (currentController->GetState() >= CasterState::EndTurn)
    {
        m_BattleManager->SwapCaster();
    }
}

void PlayerCastUpdate(float dt)
{
    CasterController* currentController = BattleManager::GetInstance()->GetCurrentCaster();
    SpellCaster* currentCaster = currentController->GetSpellCaster();
    CasterData* casterData = currentCaster->GetCasterData();

    if (Input::IsKeyBeginPressed(GLFW_KEY_1))
    {
        currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });
    }
    if (Input::IsKeyBeginPressed(GLFW_KEY_2))
    {
        currentCaster->SetPentagramData({ 1, 1, 2, 2, 2 });
    }

    int spellCost = currentCaster->GetSpellCost();
    int canCostSpell = currentCaster->GetMana() - spellCost;
    if (Input::IsKeyBeginPressed(GLFW_KEY_3)) //Invoke
    {
        if (canCostSpell >= 0)
        {
            BattleManager::GetInstance()->GetTimeline()->AddSpellToTimeline(currentController->CastSpell());
        }
        else
        {
            std::cout << "NO MANA\n";
        }
    }
    if (Input::IsKeyBeginPressed(GLFW_KEY_4))//End Turn
    {
        currentController->EndTurn(true);
    }
}

void BattleScene::ResolveStateUpdate(float dt)
{
}

void BattleScene::GameSceneLoad()
{
    std::cout << "Battle Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    m_BattleManager = BattleManager::GetInstance();

    m_BattleManager->AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player), &PlayerCastUpdate));

    m_BattleManager->StartBattle();
    std::cout << "Battle Scene : Initialize Completed\n";
}

void BattleScene::GameSceneUpdate(float dt)
{
    if (Input::IsKeyBeginPressed(GLFW_KEY_8))
    {
        std::cout << "\t Battle State: " << (int)m_BattleManager->GetBattleState() <<"\n";
    }

    switch (m_BattleManager->GetBattleState())
    {
    case BattleState::InvokeState:
        CastStateUpdate(dt);
        break;
    case BattleState::ResolveState:
        ResolveStateUpdate(dt);
        break;
    }

}

void BattleScene::GameSceneDraw()
{
    ShaderCollector* shaderCollector = EngineDataCollector::GetInstance()->GetShaderCollector();
    // Render GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        // If current Object was child -> no need to draw
        if (objectsList[idx]->parent != nullptr || !objectsList[idx]->isActive())
        {
            continue;
        }

        objectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
    }
    // Render UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        // If current Object was child -> no need to draw
        if (uiObjectsList[idx]->parent != nullptr || !uiObjectsList[idx]->isActive())
        {
            continue;
        }

        uiObjectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
    }
}

void BattleScene::GameSceneUnload()
{
    // Unload GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        objectsList[idx]->UnloadMesh();
    }
    // Unload UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        uiObjectsList[idx]->UnloadMesh();
    }
    std::cout << "Battle Scene : UnLoad Mesh Completed\n";
}

void BattleScene::GameSceneFree()
{

    //Free Battle Manager
    delete m_BattleManager;

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
