#include "Engine/ArcantEngine.h"
#include "Engine/GameStateController.h"
#include "Engine/Collector/EngineDataCollector.h"

ArcantEngine* engine = nullptr;
GameStateController* gameStateController = nullptr;
EngineDataCollector* engineDataCollector = nullptr;

int main()
{
	// Initialize Engine
	engine = ArcantEngine::GetInstance();
	engine->Init();

	// Initialize gameStateController
	gameStateController = GameStateController::GetInstance();
	gameStateController->Init(GameState::GS_MENU_SCENE);

	// Initialize ShaderCollector(For collecting type of Shader)
	// Initialize FontCollector(For collecting type of Font)
	// Initialize TextureCollector(For collecting all of texture in game)
	engineDataCollector = EngineDataCollector::GetInstance();

	double currTime = 0;
	double prevTime = 0;
	while (engine->IsRunning())
	{
		currTime = glfwGetTime();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gameStateController->currentScene->GameSceneUpdate(currTime - prevTime);

		if (gameStateController->currentState == GameState::GS_QUIT)
		{
			break;
		}

		gameStateController->currentScene->GameSceneDraw();

		// Clear User-Input
		Input::EndFrame();

		// Receive Input from User
		engine->GetWindow()->PollEvents();
		engine->GetWindow()->SwapBuffers();

		prevTime = currTime;
	}
	gameStateController->currentScene->GameSceneUnload();
	gameStateController->currentScene->GameSceneFree();

	// Deallocate instance
	engine->Free();
	gameStateController->Free();
	engineDataCollector->Free();
}