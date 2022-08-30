#pragma once
#include "Engine/GameScene.h"
#include "Game/BattleScene/BattleManager.h"
class BattleScene :public GameScene
{
private:
    BattleManager* m_BattleManager = nullptr;

    void InvokeStateUpdate();
    void ResolveStateUpdate();
public:
    virtual void GameSceneLoad() override;
    virtual void GameSceneInit() override;
    virtual void GameSceneUpdate(double dt) override;
    virtual void GameSceneDraw() override;
    virtual void GameSceneUnload() override;
    virtual void GameSceneFree() override;
};

