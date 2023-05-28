#pragma once

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

class OptionMenuObject : public UIObject
{
	private:
		UIObject* bgMenu;
		Slider* VolumeSlider[3];
		TextObject* VolumeText[3];
		Button* closeButton;

		TextObject* windowSettingText;
		Button* windowSettingButton;

	public:
		OptionMenuObject();

		Button* GetCloseButton() const;
};