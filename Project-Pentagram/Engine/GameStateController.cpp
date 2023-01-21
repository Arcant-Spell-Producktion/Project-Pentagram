#include "GameStateController.h"

GameStateController::GameStateController()
	: currentState(GameState::GS_NONE), 
	  nextState(GameState::GS_NONE), 
	  currentScene(nullptr)
{
}

void GameStateController::InitGameScene(GameState state)
{
	currentState = state;
	UpdateGameScene();
}
void GameStateController::UpdateGameScene()
{
	if (currentState == GameState::GS_QUIT)
	{
		return;
	}

	switch (currentState)
	{
		case GameState::GS_LOAD_SCENE :
			currentScene = new LoadScene();
			break;
		case GameState::GS_MENU_SCENE :
			currentScene = new MenuScene();
			break;
		case GameState::GS_NODE_SCENE :
			currentScene = new NodeScene();
			break;
        case GameState::GS_CHARACTER_SCENE:
            currentScene = new CharacterSelectScene();
            break;
		case GameState::GS_DEMO_SCENE :
			currentScene = new DemoScene();
			break;
		case GameState::GS_BATTLE_SCENE :
            currentScene = new BattleScene();
			break;
	}

	currentScene->GameSceneLoad();
	currentScene->GameSceneInit();

}
void GameStateController::UpdateGameState()
{
	if (this->nextState != GameState::GS_NONE)
	{
		// Unload and Free Old Scene
		this->currentScene->GameSceneUnload();
		this->currentScene->GameSceneFree();
		
		// Free-Memory on Old Scene
		delete this->currentScene;
		this->currentScene = nullptr;

		// Create New Scene from nextState
		this->InitGameScene(nextState);

		// Reset nextState to Default (GS::NONE)
		this->nextState = GameState::GS_NONE;
	}
}

void GameStateController::Free()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
	Singleton::Free();
}