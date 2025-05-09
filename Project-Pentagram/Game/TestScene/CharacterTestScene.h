﻿#pragma once
#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Collector/EngineDataCollector.h"

class CharacterTestScene :public GameScene
{
private:
    float test_track_t = 0.0f;

    PlayerAidUI* playerAidUI;

public:
    virtual void GameSceneLoad() override;
    virtual void GameSceneInit() override;
    virtual void GameSceneUpdate(float dt) override;
    virtual void GameSceneUnload() override;
    virtual void GameSceneFree() override;
};
