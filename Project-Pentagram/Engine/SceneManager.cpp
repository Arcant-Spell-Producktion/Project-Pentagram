#include "SceneManager.h"

namespace SceneManager
{
	void LoadScene(GameState newState)
	{
		GameStateController* gameStateController = GameStateController::GetInstance();
		if (newState == GameState::GS_RESTART)
		{
			newState = gameStateController->currentState;
		}
		gameStateController->nextState = newState;
	}
	void RestartScene()
	{
		GameStateController* gameStateController = GameStateController::GetInstance();
		gameStateController->nextState = gameStateController->currentState;
	}
	void QuitGame()
	{
		GameStateController* gameStateController = GameStateController::GetInstance();

		gameStateController->currentState = GameState::GS_QUIT;
	}
}