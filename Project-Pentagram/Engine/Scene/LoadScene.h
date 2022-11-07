#pragma once

#include <future>
#include <thread>
#include <chrono>

#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Collector/EngineDataCollector.h"
#include "Utilities/Color.h"
#include "Utilities/Thread.h"

class LoadScene : public GameScene
{
	protected:
		Thread textureThread;
		Thread utilityThread;
		std::atomic<int> loadDoneCount = 0;
	public:
		void GameSceneLoadTextureResource(EngineDataCollector* engineDataCollector);
		void GameSceneLoadUtilityResource(EngineDataCollector* engineDataCollector);

		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(float dt) override;
		virtual void GameSceneFree() override;

};