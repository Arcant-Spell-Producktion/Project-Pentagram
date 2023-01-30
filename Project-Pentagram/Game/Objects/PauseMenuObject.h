#pragma once

#include "Engine/UIObject.h"
#include "Engine/Button.h"
#include "Engine/SceneManager.h"

#include "Game/Objects/OptionMenuObject.h"

class PauseMenuObject : public UIObject
{
	private:
		UIObject* bgMenu;
		Button* resumeButton;
		Button* optionButton;
		Button* exitToMenuButton;
		Button* exitGameButton;
		OptionMenuObject* optionMenuObject;
	public:
		PauseMenuObject() : UIObject("PauseMenuObject")
		{
			this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

			bgMenu = new UIObject("BackgroundMenu");
			bgMenu->scale = { 500.0f, 500.0f, 1.0f };
			bgMenu->color = { 0.8f, 0.8f, 0.8f, 1.0f };
			SetChildRenderBack(bgMenu);

			resumeButton = new Button("ResumeButton");
			resumeButton->position = { 0.0f, 150.0f, 0.0f };
			resumeButton->scale = { 325.0f, 75.0f, 1.0f };
			resumeButton->textObject.text = "Resume";
			resumeButton->onClick.AddListener([this](Button* button) { SetActive(false); });
			SetChildRenderFront(resumeButton);

			optionButton = new Button("OptionButton");
			optionButton->position = { 0.0f, 50.0f, 0.0f };
			optionButton->scale = { 325.0f, 75.0f, 1.0f };
			optionButton->textObject.text = "Options";
			optionButton->onClick.AddListener([this](Button* button) { optionMenuObject->SetActive(true); });
			SetChildRenderFront(optionButton);

			exitToMenuButton = new Button("ExitMenuButton");
			exitToMenuButton->position = { 0.0f, -50.0f, 0.0f };
			exitToMenuButton->scale = { 325.0f, 75.0f, 1.0f };
			exitToMenuButton->textObject.text = "Exit To Menu";
			exitToMenuButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_MENU_SCENE); });
			SetChildRenderFront(exitToMenuButton);

			exitGameButton = new Button("ExitGameButton");
			exitGameButton->position = { 0.0f, -150.0f, 0.0f };
			exitGameButton->scale = { 325.0f, 75.0f, 1.0f };
			exitGameButton->textObject.text = "Exit Game";
			exitGameButton->onClick.AddListener([this](Button* button) { SceneManager::LoadScene(GameState::GS_QUIT); });
			SetChildRenderFront(exitGameButton);

			optionMenuObject = new OptionMenuObject();
			optionMenuObject->SetActive(false);
			SetChildRenderFront(optionMenuObject);
		}

		virtual void SetActive(const bool& active) override
		{
			GameObject::SetActive(active);
			optionMenuObject->SetActive(false);
		}
};