#pragma once

#include "GameState.h"
#include "GameScene.h"
#include "Scene/MenuScene.h"
#include "Scene/NodeScene.h"

class GameStateController
{
	private:
		static GameStateController* instance;
	public:
		GameScene* currentScene;
		GameState currentState;
		
		GameStateController();
		void Init(GameState state);
		void Update();

		static GameStateController* GetInstance();
		void Free();
};