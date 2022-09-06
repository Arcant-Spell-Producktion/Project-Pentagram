#include "BattleScene.h"
#include "Game/GameData/RuntimeGameData.h"
#include "SpellCaster/PlayerController.h"


void BattleScene::CastStateUpdate(float dt)
{
    CasterController* currentController = m_BattleManager->GetCurrentCaster();//Using currentCaster to display appropriate SpellCircle

    if (dynamic_cast<PlayerController*>(currentController) != nullptr)
    {
        PlayerCastUpdate(dt);
    }

    
}

void BattleScene::PlayerCastUpdate(float dt)
{
    CasterController* currentController = m_BattleManager->GetCurrentCaster();
    SpellCaster* currentCaster = currentController->GetSpellCaster();
    CasterData* casterData = currentCaster->GetCasterData();

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
            m_BattleManager->GetTimeline()->AddSpellToTimeline(currentController->CastSpell());
            m_BattleManager->SetBattleState(BattleState::CastConfirmState);
            currentController->EndTurn();
        }
        else
        {
            std::cout << "NO MANA\n";
        }
    }
    if (Input::IsKeyBeginPressed(GLFW_KEY_4) || currentCaster->GetMana() == 0)//End Turn
    {
        currentController->EndTurn(true);
    }
}

void BattleScene::ResolveStateUpdate(float dt)
{
    for (int i = 0; i < 10; i++)
    {
        SpellTimetrack* track = m_BattleManager->GetTimeline()->GetTimetrack(i);
        CasterPosition casterToResolve = track->GetWinCaster();

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
            return;
        }
    }
    m_BattleManager->GetTimeline()->UpdateTimeline();


    //if(battle end)
    //{}
    //else
    m_BattleManager->SetBattleState(BattleState::CastState);
}

void BattleScene::GameSceneLoad()
{
    std::cout << "Battle Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    m_BattleManager = BattleManager::GetInstance();

    m_BattleManager->AddCaster(new PlayerController(*(RuntimeGameData::GetInstance()->Player)));

    m_BattleManager->StartBattle();
    std::cout << "Battle Scene : Initialize Completed\n";
}

void BattleScene::GameSceneUpdate(float dt)
{
    if (Input::IsKeyBeginPressed(GLFW_KEY_R))
    {
        SceneManager::LoadScene(GameState::GS_RESTART);
        // If not return will cause memory problem
        return;
    }

    switch (m_BattleManager->GetBattleState())
    {
    case BattleState::CastState:
        CastStateUpdate(dt);
        break;
    case BattleState::CastConfirmState:
        if (m_BattleManager->GetCurrentCaster()->GetState() >= CasterState::EndTurn)
        {
            m_BattleManager->SwapCaster();
        }
        break;
    case BattleState::ResolveState:
        ResolveStateUpdate(dt);
        break;
    }

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
