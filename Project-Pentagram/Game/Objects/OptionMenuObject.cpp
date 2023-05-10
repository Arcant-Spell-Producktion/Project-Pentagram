#include "OptionMenuObject.h"

OptionMenuObject::OptionMenuObject() : UIObject("Sound Setting")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	bgMenu = new UIObject("BackgroundMenu");
	bgMenu->SetTexture("Sprites/UI/Game/ui_game_pause-panel.png");
	bgMenu->scale = { 1100.0f, 500.0f, 1.0f };
	bgMenu->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	bgMenu->SetBlockRaycast(true);
	bgMenu->SetIsSlicing(true);
	bgMenu->SetSlicingType(SlicingType::REPEAT);
	bgMenu->SetSlicingBorderSize(180.0f);
	bgMenu->SetSlicingBorderMultiplier(0.5f);
	SetChildRenderBack(bgMenu);

	#pragma region Master_Volume_UI
		VolumeSlider[VolumeType::MASTER] = new Slider("MasterVolumeSlider");
		VolumeSlider[VolumeType::MASTER]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance()->SetMasterVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdateVolume();
		};
		VolumeSlider[VolumeType::MASTER]->position = { 150.0f, 150.0f, 0.0f };
		VolumeSlider[VolumeType::MASTER]->SetValue(AudioEngine::GetInstance()->GetMasterVolume());
		VolumeSlider[VolumeType::MASTER]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::MASTER] = new TextObject("MasterVolumeText");
		VolumeText[VolumeType::MASTER]->position = { -450.0f, 150.0f, 0.0f };
		VolumeText[VolumeType::MASTER]->text = "MasterVolume";
		VolumeText[VolumeType::MASTER]->color = AC_BLACK;
		VolumeText[VolumeType::MASTER]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::MASTER]);
		SetChildRenderFront(VolumeText[VolumeType::MASTER]);
	#pragma endregion

	#pragma region BGM_UI
		VolumeSlider[VolumeType::BGM] = new Slider("BGMVolumeSlider");
		VolumeSlider[VolumeType::BGM]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance()->SetBGMVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdateVolume();
		};
		VolumeSlider[VolumeType::BGM]->position = { 150.0f, 50.0f, 0.0f };
		VolumeSlider[VolumeType::BGM]->SetValue(AudioEngine::GetInstance()->GetBGMVolume());
		VolumeSlider[VolumeType::BGM]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::BGM] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::BGM]->position = { -450.0f, 50.0f, 0.0f };
		VolumeText[VolumeType::BGM]->text = "BGMVolume";
		VolumeText[VolumeType::BGM]->color = AC_BLACK;
		VolumeText[VolumeType::BGM]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::BGM]);
		SetChildRenderFront(VolumeText[VolumeType::BGM]);
	#pragma endregion

	#pragma region SFX_UI
		VolumeSlider[VolumeType::SFX] = new Slider("SFXVolumeSlider");
		VolumeSlider[VolumeType::SFX]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance()->SetSFXVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdateVolume();
		};
		VolumeSlider[VolumeType::SFX]->position = { 150.0f, -50.0f, 0.0f };
		VolumeSlider[VolumeType::SFX]->SetValue(AudioEngine::GetInstance()->GetSFXVolume());
		VolumeSlider[VolumeType::SFX]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::SFX] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::SFX]->position = { -450.0f, -50.0f, 0.0f };
		VolumeText[VolumeType::SFX]->text = "SFXVolume";
		VolumeText[VolumeType::SFX]->color = AC_BLACK;
		VolumeText[VolumeType::SFX]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::SFX]);
		SetChildRenderFront(VolumeText[VolumeType::SFX]);
	#pragma endregion

	#pragma region Window_Setting_UI
		Window* window = ArcantEngine::GetInstance()->GetWindow();

		windowSettingText = new TextObject("WindowSettingText");
		windowSettingText->position = { -450.0f, -150.0f, 0.0f };
		windowSettingText->text = "FullScreen Mode";
		windowSettingText->color = AC_BLACK;
		windowSettingText->fontSize = 36.0f;
		windowSettingButton = new Button("WindowSettingButton");
		windowSettingButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
		windowSettingButton->SetSlicingBorderMultiplier(0.25f);
		windowSettingButton->SetSlicingType(SlicingType::REPEAT);
		windowSettingButton->SetSlicingBorderSize(120.0f);
		windowSettingButton->onHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png"); };
		windowSettingButton->onPress = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png"); };
		windowSettingButton->unHover = [this](Button* button) { button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png"); };
		windowSettingButton->textObject.text = (window->IsFullScreen() ? "On" : "Off");
		windowSettingButton->position = { 150.0f, -150.0f, 0.0f };
		windowSettingButton->scale = { 250.0f, 90.0f, 0.0f };
		windowSettingButton->onClick.AddListener([this, window](Button* button)
			{
				if (button->textObject.text == "Off")
				{
					button->textObject.text = "On";
					window->SetFullScreen(true);
				}
				else
				{
					button->textObject.text = "Off";
					window->SetFullScreen(false);
				}
			});
		SetChildRenderFront(windowSettingText);
		SetChildRenderFront(windowSettingButton);
	#pragma endregion

	#pragma region Close_Button_UI
		closeButton = new Button("CloseButton");
		closeButton->position = { 500.0f, 250.0f, 0.0f };
		closeButton->scale = { 50.0f, 50.0f, 1.0f };
		closeButton->textObject.text = "X";
		closeButton->onClick.AddListener([this](Button* button) { this->SetActive(false); });
		SetChildRenderFront(closeButton);
	#pragma endregion

}