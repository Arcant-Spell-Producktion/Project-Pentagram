#pragma once
#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Collector/EngineDataCollector.h"
#include "Game/BattleScene/BattleManager.h"

class BattleScene :public GameScene
{
    private:
        BattleManager* m_BattleManager = nullptr;

        void CastStateUpdate(float dt);
        void PlayerCastUpdate(float dt);
        void EnemyCastUpdate(float dt) {};
        void ResolveStateUpdate(float dt);
    public:
        virtual void GameSceneLoad() override;
        virtual void GameSceneInit() override;
        virtual void GameSceneUpdate(float dt) override;
        virtual void GameSceneFree() override;
};
