#pragma once

#include <future>
#include <thread>
#include <chrono>
#include <filesystem>
#include <mutex>

#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Collector/EngineDataCollector.h"
#include "Utilities/Color.h"
#include "Utilities/Thread.h"

class LoadScene : public GameScene
{
	protected:
		Thread m_LoadUtilityThread;
		Thread m_TextureThread;
		std::atomic<int> m_IsLoadDone = 0;
		int temp = 0;
	public:
		void GameSceneLoadUtilityResource(EngineDataCollector* engineDataCollector);
		void GameSceneLoadTextureResource(EngineDataCollector* engineDataCollector, const std::string& filePath);

		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(float dt) override;
		virtual void GameSceneFree() override;
};