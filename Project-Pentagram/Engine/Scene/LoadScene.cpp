#include "LoadScene.h"

void LoadScene::GameSceneLoad()
{
	std::cout << "LoadScene : Load Completed\n";
}

void LoadScene::GameSceneInit()
{
	EngineDataCollector* engineDataCollector = EngineDataCollector::GetInstance();
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();
	std::cout << "LoadScene : Free Memory\n";
}