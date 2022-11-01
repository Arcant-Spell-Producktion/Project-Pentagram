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
		Thread loadThread;
		std::atomic<bool> isLoadDone = false;
	public:
		void GameSceneLoadResource(EngineDataCollector* engineDataCollector);

		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(float dt) override;
		virtual void GameSceneFree() override;

};