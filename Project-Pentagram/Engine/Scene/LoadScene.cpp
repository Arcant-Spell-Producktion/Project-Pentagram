#include "LoadScene.h"

void LoadScene::GameSceneLoadUtilityResource(EngineDataCollector& engineDataCollector)
{
	m_LoadUtilityThread.MakeContext();
	engineDataCollector.LoadResource();
	m_IsLoadDone++;
}
void LoadScene::GameSceneLoadTextureResource(EngineDataCollector& engineDataCollector, const std::string& filePath)
{
	m_TextureThread.MakeContext();
	std::string start = "START : " + filePath + "\n\n";
	std::cout << start;
	engineDataCollector.GetTextureCollector()->LoadFile(filePath);
	//std::cout << "LOG : " << curFilePath << " is DONE!!!!\n";
	m_IsLoadDone++;
}

void LoadScene::GameSceneLoad()
{
	std::cout << "LoadScene : Load Completed\n";
}

GameObject* obj;

void LoadScene::GameSceneInit()
{
	EngineDataCollector& engineDataCollector = EngineDataCollector::GetInstance();
	engineDataCollector.GetTextureCollector()->PreLoadResource();

	// engineDataCollector->LoadResource();
	// engineDataCollector->GetTextureCollector()->LoadFile("Sprites");

	// Load Utility Resource (Sound, Font)
	m_LoadUtilityThread.SetFunction([&](LoadScene* loadScene) {loadScene->GameSceneLoadUtilityResource(engineDataCollector); }, this);

	// Load Texture Resource
	m_TextureThread.SetFunction([&](LoadScene* loadScene) {loadScene->GameSceneLoadTextureResource(engineDataCollector, "Sprites"); }, this);

	obj = CreateGameObject("Object");
	obj->SetTexture("Sprites/PreLoad/Loading.png");
	obj->scale = { 300.0f, 300.0f, 1.0f };
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	if (m_IsLoadDone == 2)
	{
		m_LoadUtilityThread.Join();
		m_TextureThread.Join();
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}
	obj->rotation += 100.0f * dt;
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();

	std::cout << "LoadScene : Free Memory\n";
}