#include "BattleScene.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SpellCaster/PlayerController.h"


void BattleScene::CastStateUpdate(float dt)
{
    CasterController* currentController = m_BattleManager->GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle

    if (currentController->GetState() != CasterState::Passed)
    {
        if (dynamic_cast<PlayerController*>(currentController) != nullptr)
        {
            PlayerCastUpdate(dt);
        }
        else
        {
            std::cout << " ***************************\n\tCheck value : " << (int)currentController->GetState() << "\n\n";
            SpellCaster* currentCaster = currentController->GetSpellCaster();

            currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });
            m_BattleManager->GetData()->Timeline.AddSpellToTimeline(currentController->CastSpell());

            currentCaster->SetPentagramData({ 1, 1, 1, 1, 3 });
            m_BattleManager->GetData()->Timeline.AddSpellToTimeline(currentController->CastSpell());


            currentController->EndTurn(true);
            m_BattleManager->SwapCaster();
        }
    }
    else
    {
        m_BattleManager->SwapCaster();
    }

}

void BattleScene::PlayerCastUpdate(float dt)
{
    CasterController* currentController = m_BattleManager->GetCurrentCaster();
    SpellCaster* currentCaster = currentController->GetSpellCaster();

    if (currentCaster == nullptr) currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });


    if (Input::IsKeyBeginPressed(GLFW_KEY_1))
    {
        currentCaster->SetPentagramData({ 1, 1, 1, 1, 1 });
    }
    if (Input::IsKeyBeginPressed(GLFW_KEY_2))
    {
        currentCaster->SetPentagramData({ 1, 1, 2, 2, 5 });
    }

    int spellCost = currentCaster->GetSpellCost();
    int canCostSpell = currentCaster->GetMana() - spellCost;
    if (Input::IsKeyBeginPressed(GLFW_KEY_3)) //Invoke
    {
        if (canCostSpell >= 0)
        {
            std::cout << "-----------------------\n\tCheck value : " << (int)currentCaster->GetCasterData()->GetPosition() << "\n\n";

            m_BattleManager->GetData()->Timeline.AddSpellToTimeline(currentController->CastSpell());
            currentController->EndTurn();
            m_BattleManager->SwapCaster();
        }
        else
        {
            std::cout << "NO MANA\n";
        }
    }
    if (Input::IsKeyBeginPressed(GLFW_KEY_4) || currentCaster->GetMana() == 0)//End Turn
    {
        currentController->EndTurn(true);
        m_BattleManager->SwapCaster();
    }
}

void BattleScene::ResolveStateUpdate(float dt)
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Resovel Track: " << i << "\n";
        SpellTimetrack* track = m_BattleManager->GetData()->Timeline.GetTimetrack(i);
        std::cout << "\tGet Track: " << i << "\n";
        CasterPosition casterToResolve = track->GetWinCaster();
        std::cout << "\tGet casterToResolve: " << (int)casterToResolve << "\n";
        //use casterToResolve play WillCompare Animation

        track->UpdateTimetrack();

        if (casterToResolve >= CasterPosition::CasterA)
        {
            for (CastSpellDetail* spell: track->GetSpellList())
            {
                if (spell->isCasted) continue;

                //TODO: resolve the spell

                spell->isCasted = true;

                //TODO: check battle end condition
            }
        }
        else
        {
            continue;
        }
    }
    m_BattleManager->GetData()->Timeline.UpdateTimeline();

    //if(battle end)
    //{}
    //else
    m_BattleManager->StandbyAllCaster();
    m_BattleManager->SetBattleState(BattleState::CastState);
    m_BattleManager->SwapCaster();
}

void BattleScene::GameSceneLoad()
{
    std::cout << "Battle Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    m_BattleManager = BattleManager::GetInstance();

    m_BattleManager->Init();

    std::cout << "Battle Scene : Initialize Completed\n";

    m_BattleManager->StartBattle();
}

void BattleScene::GameSceneUpdate(float dt)
{
    if (Input::IsKeyBeginPressed(GLFW_KEY_R))
    {
        SceneManager::LoadScene(GameState::GS_RESTART);
        // If not return will cause memory problem
        return;
    }

    switch (m_BattleManager->GetBattleStates()->StateID)
    {
    case BattleState::CastState:
        CastStateUpdate(dt);
        break;
    case BattleState::ResolveState:
        ResolveStateUpdate(dt);
        break;
    }

}

void BattleScene::GameSceneUnload()
{
    //Free Battle Manager
    m_BattleManager->Free();
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
