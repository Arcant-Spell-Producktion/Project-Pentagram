#pragma once

#include "Engine/GameObject.h"

#include "Engine/UIObject.h"
#include "Engine/Slider.h"
#include "Engine/Audio/AudioEngine.h"
#include "Engine/Audio/AudioController.h"

#include "Game/Objects/StaticButton.h"

#include "Utilities/Color.h"

enum VolumeType
{
	MASTER, BGM, SFX
};

class OptionMenuObject : public UIObject
{
	private:
		UIObject* blackBGMenu;
		UIObject* bgMenu;
		Slider* VolumeSlider[3];
		TextObject* VolumeText[3];
		StaticButton* closeButton;

		TextObject* windowSettingText;
		StaticButton* windowSettingButton;

	public:
		OptionMenuObject();

		Button* GetCloseButton() const;
};