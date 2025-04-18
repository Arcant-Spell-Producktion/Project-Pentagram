#include "SceneManager.h"

namespace SceneManager
{
	void LoadScene(GameState newState)
	{
		GameStateController& gameStateController = GameStateController::GetInstance();
		if (newState == GameState::GS_RESTART)
		{
			newState = gameStateController.currentState;
		}
		else if (newState == GameState::GS_QUIT)
		{
			gameStateController.currentState = GameState::GS_QUIT;
			return;
		}
		gameStateController.nextState = newState;
	}
	void RestartScene()
	{
		GameStateController& gameStateController = GameStateController::GetInstance();
		gameStateController.nextState = gameStateController.currentState;
	}
	void QuitGame()
	{
		GameStateController& gameStateController = GameStateController::GetInstance();

		gameStateController.currentState = GameState::GS_QUIT;
	}
}