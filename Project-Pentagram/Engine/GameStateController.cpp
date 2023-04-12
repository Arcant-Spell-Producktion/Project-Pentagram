#include "GameStateController.h"

#include "Game/TestScene/CharacterTestScene.h"
#include "Game/TutorialScene/TutorialScene.h"
#include "Game/TutorialScene/TutorialSelectScene.h"

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
        case GameState::GS_CHARACTER_SCENE:
            currentScene = new CharacterSelectScene();
            break;
        case GameState::GS_TEST_SCENE:
			currentScene = new CharacterTestScene();
			break;
		case GameState::GS_MAP_SCENE :
			currentScene = new MapScene();
			break;
		case GameState::GS_DEMO_SCENE :
			currentScene = new DemoScene();
			break;
		case GameState::GS_BATTLE_SCENE :
            currentScene = new BattleScene();
            break;
	    case GameState::GS_TUTORIAL_SELECT_SCENE:
            currentScene = new TutorialSelectScene();
            break;
	    case GameState::GS_TUTORIAL_SCENE:
            currentScene = new TutorialScene();
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