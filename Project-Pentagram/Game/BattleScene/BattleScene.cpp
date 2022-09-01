#include "BattleScene.h"

void BattleScene::InvokeStateUpdate()
{
}

void BattleScene::ResolveStateUpdate()
{
}

void BattleScene::GameSceneLoad()
{
    std::cout << "Node Scene : Load Completed\n";
}

void BattleScene::GameSceneInit()
{
    m_BattleManager = new BattleManager();
    m_BattleManager->AddCaster();
    std::cout << "Node Scene : Initialize Completed\n";
}

void BattleScene::GameSceneUpdate(double dt)
{
    switch (m_BattleManager->GetBattleState())
    {
    case BattleState::InvokeState:
        InvokeStateUpdate();
        break;
    case BattleState::ResolveState:
        ResolveStateUpdate();
        break;
    }
}

void BattleScene::GameSceneDraw()
{

}

void BattleScene::GameSceneUnload()
{
    std::cout << "Node Scene : UnLoad Mesh Completed\n";
}

void BattleScene::GameSceneFree()
{
    delete m_BattleManager;
    std::cout << "Node Scene : Free Memory\n";
}