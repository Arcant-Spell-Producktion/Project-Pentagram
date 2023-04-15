#pragma once

#include <vector>

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/Audio/AudioController.h"

class GameScene : public IGameObjectManager
{
	private:
		// ----------------- Button Events -----------------
		glm::vec3 FindButtonParentPosition(const Button* button);
		void UpdateButtonOnClick();
		void UpdateButtonOnHover();
		void UpdateButtonOnPress();
		void FocusObject(GameObject* obj, const bool& isFocus);

		std::map<GameObject*, glm::vec4> prevObjectColor;

	protected:
		// ----------------- Rendering Component List -----------------
		std::vector<GameObject*> objectsList;
		std::vector<UIObject*> uiObjectsList;
		std::vector<Button*> buttonObjectsList;

		std::vector<GameObject*> objectsToDeleteList;

		// ----------------- Utilities -----------------
		AudioController* audioController = AudioController::GetInstance();
		Camera camera;
		float timeScale = 1.0f;
		float scaledDeltaTime;

		virtual void AddGameObjectToList(GameObject* object) override;
		virtual void AddUIObjectToList(UIObject* object) override;
		virtual void AddButtonToList(Button* object) override;

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

		virtual GameObject* CreateGameObject(const std::string& objName = "", const int& animRow = 1, const std::vector<int>& animCol = { 1 }) override;
		virtual ParticleSystem* CreateParticle(ParticleProperty& particleProperty) override;
		virtual ParticleSystem* CreateParticle(const std::string& objName, ParticleProperty& particleProperty) override;
		virtual UIObject* CreateUIObject(const std::string& objName = "") override;
		virtual TextObject* CreateTextObject(const std::string& objName = "") override;
		virtual Button* CreateButton(const std::string& objName = "") override;
		virtual Slider* CreateSlider(const std::string& objName = "") override;

		// ----------------- Modify Object -----------------
		virtual void DeleteObjectByName(const std::string& objName) override;
		virtual void DeleteObjectByPointer(GameObject* objPtr) override;
		virtual GameObject* FindObject(const std::string& objName) override;
		void FocusObject(GameObject* focusObj);
        void UnFocusObject();

		void UpdateButtonEvents();
		void UpdateScaleDeltaTime(float deltaTime);
		void UpdateDeleteObject();

		// ----------------- Setter -----------------
		void SetTimeScale(const float& timeScale);

		// ----------------- Getter -----------------
		AudioController* GetAudioController() const;
		Camera* GetCamera();
		float GetTimeScale() const;
};