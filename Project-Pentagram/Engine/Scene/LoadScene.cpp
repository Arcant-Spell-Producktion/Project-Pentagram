#include "LoadScene.h"

void LoadScene::GameSceneLoadTextureResource(EngineDataCollector* engineDataCollector)
{
	textureThread.MakeContext();
	engineDataCollector->LoadTextureResource();
	loadDoneCount++;
}
void LoadScene::GameSceneLoadUtilityResource(EngineDataCollector* engineDataCollector)
{
	utilityThread.MakeContext();
	engineDataCollector->LoadUtilityResource();
	loadDoneCount++;
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
	utilityThread.SetFunction(std::thread(&LoadScene::GameSceneLoadUtilityResource, this, engineDataCollector));
	textureThread.SetFunction(std::thread(&LoadScene::GameSceneLoadTextureResource, this, engineDataCollector));
	obj = CreateGameObject("Object");
	obj->scale = { 100.0f, 100.0f, 1.0f };
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	if (loadDoneCount == 2)
	{
		textureThread.Join();
		utilityThread.Join();
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}
	obj->rotation += 100.0f * dt;
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();
	std::cout << "LoadScene : Free Memory\n";
}