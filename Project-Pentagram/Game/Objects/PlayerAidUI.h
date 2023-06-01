#pragma once

#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/Objects/ScrollButton.h"
#include "Game/Objects/StaticButton.h"
#include "Game/Objects/EffectAidUI.h"
#include "Game/Objects/SpellAidUI.h"
#include "Game/Objects/SpellTypeAidUI.h"
#include "Game/Spells/SpellEffectType.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"

#include "Utilities/Color.h"

class PlayerAidUI : public UIObject
{
	private:
		EffectAidUI* m_EffectAidUI;
		SpellAidUI* m_SpellAidUI;
		SpellTypeAidUI* m_SpellTypeAidUI;

		TextObject* m_PressF1;
		StaticButton* m_BackButton;
		std::vector<StaticButton*> m_PageButtons;

	public:
		PlayerAidUI();

		void ToggleEvent(float& timeScale);

		void OnUpdate(const float& dt) override;

		EffectAidUI* GetEffectAidUI() const;
		SpellAidUI* GetSpellAidUI() const;
		StaticButton* GetBackButton() const;
};