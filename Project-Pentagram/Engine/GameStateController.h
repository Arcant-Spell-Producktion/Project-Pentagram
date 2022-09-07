#pragma once

#include "Engine/GameState.h"
#include "Engine/GameScene.h"
#include "Engine/Scene/MenuScene.h"
#include "Engine/Scene/NodeScene.h"
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
