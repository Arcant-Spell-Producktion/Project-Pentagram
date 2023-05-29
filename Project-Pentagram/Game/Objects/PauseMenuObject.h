#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"
#include "Engine/SceneManager.h"

#include "Game/Objects/OptionMenuObject.h"
#include "Game/Objects/ConfirmUI.h"
#include "Game/Objects/StaticButton.h"

class PauseMenuObject : public UIObject
{
	private:
		UIObject* canvas;
		struct MenuUI : public UIObject
		{
			UIObject* MenuBG;
			StaticButton* ResumeButton;
			StaticButton* OptionButton;
			StaticButton* ExitToMenuButton;
			StaticButton* ExitGameButton;

			MenuUI() : UIObject("MenuUI") {}

		} *m_MenuUI;

		OptionMenuObject* m_OptionMenuObject;

		ConfirmUI *m_ConfirmUI;

		GameScene* currentGameScene;

		void InitMenuUI();
		void InitConfirmUI();

	public:
		PauseMenuObject();

		void ToggleEvent(float& timeScale);

		virtual void SetActive(const bool& active) override;
		void SetCurrentGameScene(GameScene* gameScene);

		GameScene* GetCurrentGameScene() const;
};