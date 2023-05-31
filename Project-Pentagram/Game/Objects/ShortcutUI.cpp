#include "ShortcutUI.h"

#include "Game/BattleScene/BattleManager.h"

ShortcutUI::ShortcutUI()
	: UIObject("ShortcutUI")
{

	BattleManager& bm = BattleManager::GetInstance();
	float offset = 10.0f;
	float offsetScreenX = 150.0f;
	float offsetScreenY = 20.0f;

	this->color.a = 0.0f;
	this->position = { WINDOW_WIDTH / 2.0f - offsetScreenX, WINDOW_HEIGHT / 2.0f - offsetScreenY, 0.0f };

	
	m_PauseButton = new ShortcutButton("Sprites/UI/Game/ui_game_topbar-icon.png", "Pause(ESC)");
	m_PauseButton->image->SetSpriteByIndex(0, 0);
	m_PauseButton->hoverText->textAlignment = TextAlignment::LEFT;
	m_PauseButton->hoverText->position.x -= m_PauseButton->scale.x / 2.0f;
	m_PauseButton->position.x -= (m_PauseButton->scale.x + offset);

	m_InfoButton = new ShortcutButton("Sprites/UI/Game/ui_game_topbar-icon.png", "Info(ALT)");
	m_InfoButton->image->SetSpriteByIndex(0, 1);
	m_InfoButton->hoverText->textAlignment = TextAlignment::MID;
	m_InfoButton->onClick.AddListener([this, &bm](Button* button) {
		
		CasterUIController* casterUI = bm.Data.GetCaster(CasterPosition::CasterA)->GetCasterUI();

		if (bm.Data.Timeline.UI->IsTimelineExpand() || casterUI->IsWheelActive())
			return;

		casterUI->SetIsShowDetail(casterUI->IsShowDetail() ? false : true);

	});

	m_HelpButton = new ShortcutButton("Sprites/UI/Game/ui_game_topbar-icon.png", "Help(F1)");
	m_HelpButton->image->SetSpriteByIndex(0, 2);
	m_HelpButton->hoverText->textAlignment = TextAlignment::RIGHT;
	m_HelpButton->hoverText->position.x += m_HelpButton->scale.x / 2.0f;
	m_HelpButton->position.x += (m_HelpButton->scale.x + offset);

	this->SetChildRenderFront(m_PauseButton);
	this->SetChildRenderFront(m_InfoButton);
	this->SetChildRenderFront(m_HelpButton);
}

ShortcutButton* ShortcutUI::GetPauseButton() const { return m_PauseButton; }
ShortcutButton* ShortcutUI::GetInfoButton() const { return m_InfoButton; }
ShortcutButton* ShortcutUI::GetHelpButton() const { return m_HelpButton; }