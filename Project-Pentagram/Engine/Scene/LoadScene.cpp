#include "LoadScene.h"

void LoadScene::GameSceneLoadUtilityResource(Thread& thread, EngineDataCollector* engineDataCollector)
{
	mtx.lock();
	thread.MakeContext();
	engineDataCollector->LoadResource();
	m_IsLoadDone++;
	mtx.unlock();
}
void LoadScene::GameSceneLoadTextureResource(Thread* thread, EngineDataCollector* engineDataCollector, const std::string& filePath)
{
	mtx.lock();
	thread->MakeContext();
	std::string start = "START : " + filePath + "\n\n";
	std::cout << start;
	std::string curFilePath = filePath;
	std::replace(curFilePath.begin(), curFilePath.end(), '\\', '/');
	engineDataCollector->GetTextureCollector()->LoadFile(curFilePath);
	//std::cout << "LOG : " << curFilePath << " is DONE!!!!\n";
	m_IsLoadDone++;
	mtx.unlock();
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

	// Load Utility Resource (Sound, Font)
	m_LoadUtilityThread.SetFunction([&](LoadScene* loadScene) {loadScene->GameSceneLoadUtilityResource(m_LoadUtilityThread, engineDataCollector); }, this);

	// Load Texture Resource
	Thread* curThread = new Thread();
	curThread->SetFunction([&](LoadScene* loadScene) {loadScene->GameSceneLoadTextureResource(curThread, engineDataCollector, "Sprites"); }, this);
	m_TextureThread.push_back(curThread);

	obj = CreateGameObject("Object");
	obj->SetTexture("Sprites/PreLoad/Loading.png");
	obj->scale = { 300.0f, 300.0f, 1.0f };
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	if (m_IsLoadDone == m_TextureThread.size() + 1)
	{
		m_LoadUtilityThread.Join();
		for (int idx = 0; idx < m_TextureThread.size(); idx++)
		{
			m_TextureThread[idx]->Join();
		}
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}
	obj->rotation += 100.0f * dt;
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();

	for (int idx = 0; idx < m_TextureThread.size(); idx++)
	{
		delete m_TextureThread[idx];
	}

	std::cout << "LoadScene : Free Memory\n";
}