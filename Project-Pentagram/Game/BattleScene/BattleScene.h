#pragma once
#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Collector/EngineDataCollector.h"

class BattleScene :public GameScene
{
    public:
        virtual void GameSceneLoad() override;
        virtual void GameSceneInit() override;
        virtual void GameSceneUpdate(float dt) override;
        virtual void GameSceneUnload() override;
        virtual void GameSceneFree() override;
};
