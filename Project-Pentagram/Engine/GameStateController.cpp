#include "GameStateController.h"

GameStateController::GameStateController()
	: currentState(GameState::GS_NONE), currentScene(nullptr)
{
}

void GameStateController::Init(GameState state)
{
	currentState = state;
	Update();
}

void GameStateController::Update()
{
	if (currentState == GameState::GS_QUIT)
	{
		return;
	}

	switch (currentState)
	{
		case GameState::GS_MENU_SCENE :
			currentScene = new MenuScene();
			break;
		case GameState::GS_NODE_SCENE :
			currentScene = new NodeScene();
			break;
		case GameState::GS_BATTLE_SCENE :
            currentScene = new BattleScene();
			break;
	}

	currentScene->GameSceneLoad();
	currentScene->GameSceneInit();

}

void GameStateController::Free()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
	Singleton::Free();
}