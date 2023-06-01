#pragma once

#include "Engine/UIObject.h"

#include "Game/Objects/StaticButton.h"

struct ArrowButton : public StaticButton
{
	UIObject* ArrowSprite;

	ArrowButton();
};