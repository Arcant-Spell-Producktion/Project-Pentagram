#pragma once

#include "GameState.h"
#include "GameStateController.h"

namespace SceneManager
{
	void LoadScene(GameState newState);
	void RestartScene();
	void QuitGame();
}