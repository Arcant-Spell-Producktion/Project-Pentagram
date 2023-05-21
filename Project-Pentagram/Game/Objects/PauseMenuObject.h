#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"
#include "Engine/SceneManager.h"

#include "Game/Objects/OptionMenuObject.h"

class PauseMenuObject : public UIObject
{
	private:
		UIObject* canvas;
		struct MenuUI : public UIObject
		{
			UIObject* MenuBG;
			Button* ResumeButton;
			Button* OptionButton;
			Button* ExitToMenuButton;
			Button* ExitGameButton;

			MenuUI() : UIObject("MenuUI") {}

		} *m_MenuUI;

		OptionMenuObject* m_OptionMenuObject;

		struct ConfirmUI : public UIObject
		{
			TextObject* ConfirmText;
			Button* Yes;
			Button* No;
			Button* CloseButton;

			ConfirmUI() : UIObject("ConfirmUI") {}

		} *m_ConfirmUI;

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