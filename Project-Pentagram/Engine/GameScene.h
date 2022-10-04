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
		// ----------------- Button Events -----------------
		glm::vec3 FindButtonParentPosition(const Button* button);
		void UpdateButtonOnClick();
		void UpdateButtonOnHover();
		void UpdateButtonOnPress();

	protected:
		// ----------------- Rendering Component List -----------------
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		std::vector<Button*> buttonObjectsList;

		std::vector<GameObject*> objectsToDeleteList;

		// ----------------- Utilities -----------------
		SoundSystem* soundSystem = EngineDataCollector::GetInstance()->GetSoundSystem();
		Camera camera;
		float timeScale = 1.0f;
		float scaledDeltaTime;

	public:

		virtual ~GameScene();

		// ----------------- GameState Loop -----------------
		virtual void GameSceneLoad() = 0;
		virtual void GameSceneInit() = 0;
		virtual void GameSceneUpdate(float dt);
		virtual void GameSceneDraw();
		virtual void GameSceneUnload();
		virtual void GameSceneFree();

		// ----------------- Creating Object -----------------
		template <typename T>
        T* CreateObject(T* object)
        {
            if (Button* button = dynamic_cast<Button*>(object))
            {
                uiObjectsList.push_back(button);
                buttonObjectsList.push_back(button);
            }
            else if (UIObject* ui = dynamic_cast<UIObject*>(object))
            {
                uiObjectsList.push_back(ui);
            }
            else if (GameObject* gameObj = dynamic_cast<GameObject*>(object))
            {
                objectsList.push_back(gameObj);
            }
            return object;
        }

		GameObject* CreateGameObject(const std::string& objName = "", const int& animRow = 1, const std::vector<int>& animCol = { 1 });
		ParticleSystem* CreateParticle(ParticleProperty& particleProperty);
		ParticleSystem* CreateParticle(const std::string& objName, ParticleProperty& particleProperty);
		UIObject* CreateUIObject(const std::string& objName = "");
		TextObject* CreateTextObject(const std::string& objName = "");
		Button* CreateButton(const std::string& objName = "");
		Slider* CreateSlider(const std::string& objName = "");

		// ----------------- Modify Object -----------------
		void DeleteObjectByName(const std::string& objName);
		void DeleteObjectByPointer(GameObject* objPtr);
		GameObject* FindObject(const std::string& objName);

		void UpdateButtonEvents();
		void UpdateScaleDeltaTime(float deltaTime);
		void UpdateDeleteObject();
};