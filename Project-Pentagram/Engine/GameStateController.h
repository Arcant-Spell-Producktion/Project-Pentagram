#pragma once

#include "Engine/GameState.h"
#include "Engine/GameScene.h"
#include "Engine/Scene/MenuScene.h"
#include "Engine/Scene/NodeScene.h"
#include "Engine/Scene/LoadScene.h"
#include "Game/BattleScene/BattleScene.h"
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
