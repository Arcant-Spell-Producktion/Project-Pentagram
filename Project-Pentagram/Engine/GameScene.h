#pragma once

#include <vector>

#include "GameObject.h"
#include "ParticleSystem.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"
#include "Button.h"
#include "Camera.h"

class GameScene
{
	protected:
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		Camera camera;

	public:

		// GameState Loop
		virtual void GameSceneLoad() = 0;
		virtual void GameSceneInit() = 0;
		virtual void GameSceneUpdate(double dt) = 0;
		virtual void GameSceneDraw() = 0;
		virtual void GameSceneUnload() = 0;
		virtual void GameSceneFree() = 0;

		// Create Object
		GameObject* CreateGameObject(const std::string& objName = "");
		ParticleSystem* CreateParticle(ParticleProps& particleProps);
		ParticleSystem* CreateParticle(const std::string& objName, ParticleProps& particleProps);
		UIObject* CreateUIObject(const std::string& objName = "");
		TextObject* CreateTextObject(const std::string& objName = "");
		Button* CreateButton(const std::string& objName = "");
};