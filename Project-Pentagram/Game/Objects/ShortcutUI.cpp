#include "ShortcutUI.h"

#include "Game/BattleScene/BattleManager.h"

ShortcutUI::ShortcutUI()
	: UIObject("ShortcutUI")
{
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

	m_InfoButton->onHover = [this](Button* button)
	{
		if (BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->IsReadyToShowDetail())
		{
			button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png");
			m_InfoButton->hoverText->SetActive(true);
		}
	};
	m_InfoButton->onPress = [this](Button* button)
	{
		if (BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->IsReadyToShowDetail())
			button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
	};
	m_InfoButton->unHover = [this](Button* button)
	{
		if (BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->IsReadyToShowDetail())
		{
			button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
		}
		m_InfoButton->hoverText->SetActive(false);
	};

	m_InfoButton->onClick = [this](Button* button) {

		if (BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->IsReadyToShowDetail())
		{
			BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->SetIsShowDetail(BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI()->IsShowDetail() ? false : true);
		}
	};

	m_HelpButton = new ShortcutButton("Sprites/UI/Game/ui_game_topbar-icon.png", "Help(F1)");
	m_HelpButton->image->SetSpriteByIndex(0, 2);
	m_HelpButton->hoverText->textAlignment = TextAlignment::RIGHT;
	m_HelpButton->hoverText->position.x += m_HelpButton->scale.x / 2.0f;
	m_HelpButton->position.x += (m_HelpButton->scale.x + offset);

	this->SetChildRenderFront(m_PauseButton);
	this->SetChildRenderFront(m_InfoButton);
	this->SetChildRenderFront(m_HelpButton);
}

void ShortcutUI::OnUpdate(const float& dt)
{
	CasterUIController* casterUI = BattleManager::GetInstance().Data.GetCaster(CasterPosition::CasterA)->GetCasterUI();

	if (!casterUI->IsReadyToShowDetail())
	{
		m_InfoButton->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
	}
}

ShortcutButton* ShortcutUI::GetPauseButton() const { return m_PauseButton; }
ShortcutButton* ShortcutUI::GetInfoButton() const { return m_InfoButton; }
ShortcutButton* ShortcutUI::GetHelpButton() const { return m_HelpButton; }