#include "SceneManager.h"

namespace SceneManager
{
	void LoadScene(GameState newState)
	{
		GameStateController* gameStateController = GameStateController::GetInstance();

		// Unload and Free Old Scene
		gameStateController->currentScene->GameSceneUnload();
		gameStateController->currentScene->GameSceneFree();

		delete gameStateController->currentScene;

		gameStateController->Init(newState);
	}

	void QuitGame()
	{
		GameStateController* gameStateController = GameStateController::GetInstance();

		gameStateController->currentState = GameState::GS_QUIT;
	}
}