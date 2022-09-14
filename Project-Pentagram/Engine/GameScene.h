#pragma once

#include <vector>

#include "Engine/Input.h"
#include "Engine/GameObjectTag.h"
#include "Engine/GameObject.h"
#include "Engine/ParticleSystem.h"
#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"
#include "Engine/Button.h"
#include "Engine/Slider.h"
#include "Engine/Camera.h"

class GameScene
{
	private:
		glm::vec3 FindButtonParentPosition(const Button* button);
		void UpdateButtonOnClick();
		void UpdateButtonOnHover();
		void UpdateButtonOnPress();

	protected:
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		std::vector<Button*> buttonObjectsList;
		SoundSystem* soundSystem = EngineDataCollector::GetInstance()->GetSoundSystem();
		Camera camera;
		float timeScale = 1.0f;

	public:

		virtual ~GameScene();

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
		Slider* CreateSlider(const std::string& objName = "");

		void UpdateButtonEvents();
};