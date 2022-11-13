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
		std::vector<Thread*> m_TextureThread;
		std::atomic<int> m_IsLoadDone = 0;
		std::mutex mtx;
	public:
		void GameSceneLoadUtilityResource(Thread& thread, EngineDataCollector* engineDataCollector);
		void GameSceneLoadTextureResource(Thread* thread, EngineDataCollector* engineDataCollector, const std::string& filePath);

		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(float dt) override;
		virtual void GameSceneFree() override;
};