#include "Engine/GameObject.h"

#include "Engine/UIObject.h"
#include "Engine/Slider.h"
#include "Engine/Audio/AudioEngine.h"
#include "Engine/Audio/AudioController.h"

#include "Utilities/Color.h"

enum VolumeType
{
	MASTER, BGM, SFX
};

class SoundSettingObject : public UIObject
{
private:
	UIObject* bgMenu;
	Slider* VolumeSlider[3];
	TextObject* VolumeText[3];
	Button* closeButton;

public:
	SoundSettingObject() : UIObject("Sound Setting")
	{
		bgMenu = new UIObject("BackgroundMenu");
		bgMenu->scale = { 1000.0f, 500.0f, 1.0f };
		bgMenu->color = { 0.8f, 0.8f, 0.8f, 1.0f };
		SetChildRenderBack(bgMenu);

		VolumeSlider[VolumeType::MASTER] = new Slider("MasterVolumeSlider");
		VolumeSlider[VolumeType::MASTER]->onValueChanged = [](Slider* slider)
		{ 
			AudioEngine::GetInstance()->SetMasterVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdate();
		};
		VolumeSlider[VolumeType::MASTER]->position = { -150.0f, 150.0f, 0.0f };
		VolumeSlider[VolumeType::MASTER]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::MASTER] = new TextObject("MasterVolumeText");
		VolumeText[VolumeType::MASTER]->position = { 150.0f, 150.0f, 0.0f};
		VolumeText[VolumeType::MASTER]->text = "MasterVolume";
		VolumeText[VolumeType::MASTER]->color = AC_BLACK;
		VolumeText[VolumeType::MASTER]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::MASTER]);
		SetChildRenderFront(VolumeText[VolumeType::MASTER]);

		VolumeSlider[VolumeType::BGM] = new Slider("BGMVolumeSlider");
		VolumeSlider[VolumeType::BGM]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance()->SetBGMVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdate();
		};
		VolumeSlider[VolumeType::BGM]->position = { -150.0f, 0.0f, 0.0f };
		VolumeSlider[VolumeType::BGM]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::BGM] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::BGM]->position = { 150.0f, 0.0f, 0.0f };
		VolumeText[VolumeType::BGM]->text = "BGMVolume";
		VolumeText[VolumeType::BGM]->color = AC_BLACK;
		VolumeText[VolumeType::BGM]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::BGM]);
		SetChildRenderFront(VolumeText[VolumeType::BGM]);

		VolumeSlider[VolumeType::SFX] = new Slider("SFXVolumeSlider");
		VolumeSlider[VolumeType::SFX]->onValueChanged = [](Slider* slider)
		{
			AudioEngine::GetInstance()->SetSFXVolume(slider->GetValue());
			AudioController::GetInstance()->OnUpdate();
		};
		VolumeSlider[VolumeType::SFX]->position = { -150.0f, -150.0f, 0.0f };
		VolumeSlider[VolumeType::SFX]->GetSliderButton()->color = AC_YELLOW;
		VolumeText[VolumeType::SFX] = new TextObject("BGMVolumeText");
		VolumeText[VolumeType::SFX]->position = { 150.0f, -150.0f, 0.0f };
		VolumeText[VolumeType::SFX]->text = "SFXVolume";
		VolumeText[VolumeType::SFX]->color = AC_BLACK;
		VolumeText[VolumeType::SFX]->fontSize = 36.0f;
		SetChildRenderFront(VolumeSlider[VolumeType::SFX]);
		SetChildRenderFront(VolumeText[VolumeType::SFX]);

		closeButton = new Button("CloseButton");
		closeButton->position = { 500.0f, 250.0f, 0.0f };
		closeButton->scale = { 50.0f, 50.0f, 1.0f };
		closeButton->textObject.text = "X";
		closeButton->onClick.AddListener([this](Button* button) { this->SetActive(false); });
		SetChildRenderFront(closeButton);
	}
};