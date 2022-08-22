#pragma once

#include "../GameScene.h"

class NodeScene : public GameScene
{
	public:
		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(double dt) override;
		virtual void GameSceneDraw() override;
		virtual void GameSceneUnload() override;
		virtual void GameSceneFree() override;
};