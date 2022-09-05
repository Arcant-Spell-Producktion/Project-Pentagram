#pragma once

#include <vector>

#include "Input.h"
#include "GameObjectTag.h"
#include "GameObject.h"
#include "ParticleSystem.h"
#include "UIObject.h"
#include "Renderer/TextObject.h"
#include "Button.h"
#include "Camera.h"

class GameScene
{
	private:
		void UpdateButtonOnClick();
		void UpdateButtonOnHover();

	protected:
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		std::vector<Button*> buttonObjectsList;
		Camera camera;

	public:

		// GameState Loop
		virtual void GameSceneLoad() = 0;
		virtual void GameSceneInit() = 0;
		virtual void GameSceneUpdate(float dt) = 0;
		virtual void GameSceneDraw();
		virtual void GameSceneUnload();
		virtual void GameSceneFree();

		// Create Object
		GameObject* CreateGameObject(const std::string& objName = "", const int& animRow = 1, const std::vector<int>& animCol = { 1 });
		ParticleSystem* CreateParticle(ParticleProps& particleProps);
		ParticleSystem* CreateParticle(const std::string& objName, ParticleProps& particleProps);
		UIObject* CreateUIObject(const std::string& objName = "");
		TextObject* CreateTextObject(const std::string& objName = "");
		Button* CreateButton(const std::string& objName = "");

		void UpdateButtonEvents();
};