#include "LoadScene.h"

void LoadScene::GameSceneLoadResource(EngineDataCollector* engineDataCollector)
{
	glfwMakeContextCurrent(offscreen_context);

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
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	offscreen_context = glfwCreateWindow(640, 480, "", NULL, ArcantEngine::GetInstance()->GetWindow()->getWindow());

	EngineDataCollector* engineDataCollector = EngineDataCollector::GetInstance();
	engineDataCollector->GetTextureCollector()->PreLoadResource();
	loadThread = std::thread(&LoadScene::GameSceneLoadResource, this, engineDataCollector);
	obj = CreateGameObject("Object");
	obj->scale = { 100.0f, 100.0f, 1.0f };
	std::cout << "LoadScene : Initialize Completed\n";
}

void LoadScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);
	if (isLoadDone)
	{
		loadThread.join();
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}
	obj->rotation += 100.0f * dt;
}

void LoadScene::GameSceneFree()
{
	GameScene::GameSceneFree();
	std::cout << "LoadScene : Free Memory\n";
}