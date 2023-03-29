#pragma once

#include "Engine/ArcantEngine.h"
#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/GameData/CasterData/PlayerData.h"
#include "Game/Spells/Element.h"

class CasterStatUI : public UIObject
{
	private:
		UIObject* m_CasterProfile;
		
		UIObject* m_ManaWheelUI;

		UIObject* m_ManaUI;
		TextObject* m_ManaTextUI;

		UIObject* m_HPUI;
		TextObject* m_HPTextUI;

	public:
		CasterStatUI(PlayerData* playerData);
};