#pragma once

#include <vector>

#include "Engine/Input.h"
#include "Engine/GameObjectTag.h"
#include "Engine/GameObject.h"
#include "Engine/ParticleSystem.h"
#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"
#include "Engine/Button.h"
#include "Engine/Camera.h"

class GameScene
{
	private:
		void UpdateButtonOnClick();
		void UpdateButtonOnHover();

	protected:
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		std::vector<Button*> buttonObjectsList;
		SoundSystem* soundSystem = EngineDataCollector::GetInstance()->GetSoundSystem();
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