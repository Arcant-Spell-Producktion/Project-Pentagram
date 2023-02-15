#pragma once

#include "Engine/GameScene.h"
#include "Engine/GameState.h"
#include "Engine/Scene/DemoScene.h"
#include "Engine/Scene/LoadScene.h"
#include "Engine/Scene/MenuScene.h"
#include "Game/BattleScene/BattleScene.h"
#include "Game/CharacterSelectScene/CharacterSelectScene.h"
#include "Game/MapScene/MapScene.h"
#include "Utilities/Singleton.h"

class GameStateController : public Singleton<GameStateController>
{
	public:
		GameScene* currentScene;

		GameState currentState;
		GameState nextState;

		GameStateController();
		void InitGameScene(GameState state);
		void UpdateGameScene();
		void UpdateGameState();

		void Free();
};
