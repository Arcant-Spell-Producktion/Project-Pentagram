#pragma once

#include "GameState.h"
#include "GameScene.h"
#include "Scene/MenuScene.h"
#include "Scene/NodeScene.h"
#include "Game/BattleScene/BattleScene.h"
#include "Utilities/Singleton.h"

class GameStateController : public Singleton<GameStateController>
{
	public:
		GameScene* currentScene;
		GameState currentState;
		
		GameStateController();
		void Init(GameState state);
		void Update();

		void Free();
};