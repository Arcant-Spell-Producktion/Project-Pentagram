#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"
#include "Engine/SceneManager.h"

#include "Game/Objects/OptionMenuObject.h"

class PauseMenuObject : public UIObject
{
	private:
		UIObject* canvas;
		UIObject* bgMenu;
		Button* resumeButton;
		Button* optionButton;
		Button* exitToMenuButton;
		Button* exitGameButton;
		OptionMenuObject* optionMenuObject;

		GameScene* currentGameScene;

	public:
		PauseMenuObject();

		void ToggleEvent(float& timeScale);

		virtual void SetActive(const bool& active) override;
		void SetCurrentGameScene(GameScene* gameScene);

		GameScene* GetCurrentGameScene() const;
};