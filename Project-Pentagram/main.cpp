#include "Engine/ArcantEngine.h"
#include "Engine/GameStateController.h"
#include "Engine/Renderer/ShaderCollector.h"
#include "Engine/Renderer/FontCollector.h"
#include "Game/Spells/Spell.h"

ArcantEngine* engine = nullptr;
GameStateController* gameStateController = nullptr;
ShaderCollector* shaderCollector = nullptr;
FontCollector* fontCollector = nullptr;

int main()
{
	Spell spell;
	// Initialize Engine
	engine = ArcantEngine::GetInstance();
	engine->Init();

	// Initialize gameStateController
	gameStateController = GameStateController::GetInstance();
	gameStateController->Init(GameState::GS_MENU_SCENE);

	// Initialize ShaderCollector(For collecting type of Shader)
	shaderCollector = ShaderCollector::GetInstance();

	// Initialize TextCollector(For collecting type of Font)
	fontCollector = FontCollector::GetInstance();

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
	fontCollector->Free();
}