#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"
#include "Engine/Button.h"

#include "Game/Spells/Element.h"

class MapInfoUI : public UIObject
{
	private:
		UIObject* m_InfoBG;

		TextObject* m_MapInfoText;

	public:
		Button* m_MapEnterButton;
		
		MapInfoUI();
		void SetMapInfo(const Element::Type& element);
};