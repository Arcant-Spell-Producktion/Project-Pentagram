#include "OptionMenuObject.h"

OptionMenuObject::OptionMenuObject() : UIObject("Sound Setting")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	blackBGMenu = new UIObject("BlackBackgroundMenu");
	blackBGMenu->scale = { 1920.0f, 1080.0f, 1.0f };
	blackBGMenu->color = { 0.0f, 0.0f, 0.0f, 0.75f };
	blackBGMenu->SetBlockRaycast(true);
	SetChildRenderBack(blackBGMenu);

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
		VolumeSlider[VolumeType::MASTER]->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_inactive.png");
		VolumeSlider[VolumeType::MASTER]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance().SetMasterVolume(slider->GetValue());
			AudioController::GetInstance().OnUpdateVolume();
			slider->GetForegroundUI()->SetClipPercentage(slider->GetValue());
		};
		VolumeSlider[VolumeType::MASTER]->position = { 150.0f, 150.0f, 0.0f };
		VolumeSlider[VolumeType::MASTER]->SetValue(AudioEngine::GetInstance().GetMasterVolume());
		VolumeSlider[VolumeType::MASTER]->GetSliderButton()->SetTexture("Sprites/UI/Interactable/Slider/handle/ui_interactable_slider_handle_default.png");
		VolumeSlider[VolumeType::MASTER]->GetSliderButton()->SetIsSlicing(false);
		VolumeSlider[VolumeType::MASTER]->GetForegroundUI()->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_active.png");
		VolumeSlider[VolumeType::MASTER]->GetForegroundUI()->SetIsClip(true);
		VolumeText[VolumeType::MASTER] = new TextObject("MasterVolumeText");
		VolumeText[VolumeType::MASTER]->position = { -450.0f, 150.0f, 0.0f };
		VolumeText[VolumeType::MASTER]->text = "MasterVolume";
		VolumeText[VolumeType::MASTER]->color = AC_WHITE;
		VolumeText[VolumeType::MASTER]->outlineColor = AC_BLACK;
		VolumeText[VolumeType::MASTER]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::MASTER]);
		SetChildRenderFront(VolumeText[VolumeType::MASTER]);
	#pragma endregion

	#pragma region BGM_UI
		VolumeSlider[VolumeType::BGM] = new Slider("BGMVolumeSlider");
		VolumeSlider[VolumeType::BGM]->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_inactive.png");
		VolumeSlider[VolumeType::BGM]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance().SetBGMVolume(slider->GetValue());
			AudioController::GetInstance().OnUpdateVolume();
			slider->GetForegroundUI()->SetClipPercentage(slider->GetValue());
		};
		VolumeSlider[VolumeType::BGM]->position = { 150.0f, 50.0f, 0.0f };
		VolumeSlider[VolumeType::BGM]->SetValue(AudioEngine::GetInstance().GetBGMVolume());
		VolumeSlider[VolumeType::BGM]->GetSliderButton()->SetTexture("Sprites/UI/Interactable/Slider/handle/ui_interactable_slider_handle_default.png");
		VolumeSlider[VolumeType::BGM]->GetSliderButton()->SetIsSlicing(false);
		VolumeSlider[VolumeType::BGM]->GetForegroundUI()->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_active.png");
		VolumeSlider[VolumeType::BGM]->GetForegroundUI()->SetIsClip(true);
		VolumeText[VolumeType::BGM] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::BGM]->position = { -450.0f, 50.0f, 0.0f };
		VolumeText[VolumeType::BGM]->text = "BGMVolume";
		VolumeText[VolumeType::BGM]->color = AC_WHITE;
		VolumeText[VolumeType::BGM]->outlineColor = AC_BLACK;
		VolumeText[VolumeType::BGM]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::BGM]);
		SetChildRenderFront(VolumeText[VolumeType::BGM]);
	#pragma endregion

	#pragma region SFX_UI
		VolumeSlider[VolumeType::SFX] = new Slider("SFXVolumeSlider");
		VolumeSlider[VolumeType::SFX]->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_inactive.png");
		VolumeSlider[VolumeType::SFX]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance().SetSFXVolume(slider->GetValue());
			AudioController::GetInstance().OnUpdateVolume();
			slider->GetForegroundUI()->SetClipPercentage(slider->GetValue());
		};
		VolumeSlider[VolumeType::SFX]->position = { 150.0f, -50.0f, 0.0f };
		VolumeSlider[VolumeType::SFX]->SetValue(AudioEngine::GetInstance().GetSFXVolume());
		VolumeSlider[VolumeType::SFX]->GetSliderButton()->SetTexture("Sprites/UI/Interactable/Slider/handle/ui_interactable_slider_handle_default.png");
		VolumeSlider[VolumeType::SFX]->GetSliderButton()->SetIsSlicing(false);
		VolumeSlider[VolumeType::SFX]->GetForegroundUI()->SetTexture("Sprites/UI/Interactable/Slider/bar/ui_interactable_slider_bar_active.png");
		VolumeSlider[VolumeType::SFX]->GetForegroundUI()->SetIsClip(true);
		VolumeText[VolumeType::SFX] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::SFX]->position = { -450.0f, -50.0f, 0.0f };
		VolumeText[VolumeType::SFX]->text = "SFXVolume";
		VolumeText[VolumeType::SFX]->color = AC_WHITE;
		VolumeText[VolumeType::SFX]->outlineColor = AC_BLACK;
		VolumeText[VolumeType::SFX]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::SFX]);
		SetChildRenderFront(VolumeText[VolumeType::SFX]);
	#pragma endregion

	#pragma region Window_Setting_UI
		Window* window = ArcantEngine::GetInstance().GetWindow();

		windowSettingText = new TextObject("WindowSettingText");
		windowSettingText->position = { -450.0f, -150.0f, 0.0f };
		windowSettingText->text = "FullScreen Mode";
		windowSettingText->color = AC_WHITE;
		windowSettingText->outlineColor = AC_BLACK;
		windowSettingText->fontSize = 36.0f;
		windowSettingButton = new StaticButton("WindowSettingButton", { 250.0f, 90.0f, 0.0f });
		windowSettingButton->textObject.text = (window->IsFullScreen() ? "On" : "Off");
		windowSettingButton->position = { 150.0f, -150.0f, 0.0f };
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
		closeButton = new StaticButton("X", { 75.0f, 75.0f, 1.0f });
		closeButton->SetSlicingBorderMultiplier(0.2f);
		closeButton->position = { (bgMenu->scale.x / 2.0f) - (closeButton->scale.x / 2.0f), (bgMenu->scale.y / 2.0f) - (closeButton->scale.y / 2.0f), 0.0f };
		closeButton->textObject.fontSize = 44.0f;
		closeButton->onClick.AddListener([this](Button* button) { this->SetActive(false); });
		SetChildRenderFront(closeButton);
	#pragma endregion

}

Button* OptionMenuObject::GetCloseButton() const { return this->closeButton; }