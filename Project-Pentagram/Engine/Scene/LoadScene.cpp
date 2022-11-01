#include "LoadScene.h"

void LoadScene::GameSceneLoadResource(EngineDataCollector* engineDataCollector)
{
	loadThread.MakeContext();
	engineDataCollector->LoadResource();
	isLoadDone = true;
}

void LoadScene::GameSceneLoad()
{
	std::cout << "LoadScene : Load Completed\n";
}

GameObject* obj;

void LoadScene::GameSceneInit()
{
	EngineDataCollector* engineDataCollector = EngineDataCollector::GetInstance();
	engineDataCollector->GetTextureCollector()->PreLoadResource();
	loadThread.SetFunction(std::thread(&LoadScene::GameSceneLoadResource, this, engineDataCollector));
	obj = CreateGameObject("Object");
	obj->scale = { 100.0f, 100.0f, 1.0f };
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	if (isLoadDone)
	{
		loadThread.Join();
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}
	obj->rotation += 100.0f * dt;
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();
	std::cout << "LoadScene : Free Memory\n";
}