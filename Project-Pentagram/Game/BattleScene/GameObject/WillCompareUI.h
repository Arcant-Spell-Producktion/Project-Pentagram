#pragma once

#include "Engine/IGameObjectManager.h"
#include "Engine/Renderer/TextObject.h"

#include "Game/BattleScene/GameObject/SpellIconUI.h"

#include "Utilities/Color.h"

const float WillCompareTextSize = 32.0f;
const float WillCompareMaxTextSize = 36.0f;

class WillCompareUI : public UIObject
{
	private:
		TextObject* m_PlayerWill;
		TextObject* m_EnemyWill;

		int m_PlayerWillValue = 0;
		int m_EnemyWillValue = 0;

		// For Slightly Increase/Decrease FontSize
		int m_ExpandDir = 1;

		TextObject* GetGreaterWillObject();
		void UpdateTextSize(TextObject* casterWillUI, const float& dt);

	public:
		WillCompareUI(int trackIndex);

		virtual void OnUpdate(const float& dt) override;

		void UpdateTextWillValue(const std::vector<SpellIconUI*> &icons);
		void ResetWillCompareUI();
};
