#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Spells/Element.h"
#include "Game/CharacterSelectScene/EffectInfoUI.h"
#include "Game/CharacterSelectScene/CasterInfo.h"

#include "Utilities/Color.h"

class CharacterInfoUI : public UIObject
{
	private:
		UIObject* m_InfoBackground;
		TextObject* m_CasterInfo;
		EffectInfoUI* m_EffectInfoUI[2];

		const float offset = 50.0f;

	public:
		CharacterInfoUI();

		void UpdateSelectedCharacter(Element::Type element);
};