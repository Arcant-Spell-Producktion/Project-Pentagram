#pragma once
#include "Engine/GameScene.h"
class BattleScene :public GameScene
{
public:
    virtual void GameSceneLoad() = 0;
    virtual void GameSceneInit() = 0;
    virtual void GameSceneUpdate(double dt) = 0;
    virtual void GameSceneDraw() = 0;
    virtual void GameSceneUnload() = 0;
    virtual void GameSceneFree() = 0;
};

