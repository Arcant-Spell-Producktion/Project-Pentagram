#pragma once

#include "../GameScene.h"
#include "../SceneManager.h"
#include "../Input.h"
#include "../Renderer/ShaderCollector.h"

class MenuScene : public GameScene
{
	public:
		virtual void GameSceneLoad() override;
		virtual void GameSceneInit() override;
		virtual void GameSceneUpdate(double dt) override;
		virtual void GameSceneDraw() override;
		virtual void GameSceneUnload() override;
		virtual void GameSceneFree() override;
};