#pragma once

#include <vector>

#include "GameObject.h"
#include "UI.h"
#include "Camera.h"

class GameScene
{
	protected:
		std::vector<GameObject*> objectsList;
		std::vector<UI*> uiList;
		Camera camera;

	public:
		virtual void GameSceneLoad() = 0;
		virtual void GameSceneInit() = 0;
		virtual void GameSceneUpdate(double dt) = 0;
		virtual void GameSceneDraw() = 0;
		virtual void GameSceneUnload() = 0;
		virtual void GameSceneFree() = 0;
};