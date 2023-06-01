#include "PlayerAidUI.h"

PlayerAidUI::PlayerAidUI() : UIObject("PlayerAidUI")
{
	this->color.a = 0.0f;

	m_EffectAidUI = new EffectAidUI();
	m_SpellAidUI = new SpellAidUI();
	m_SpellTypeAidUI = new SpellTypeAidUI();

	m_PressF1 = new TextObject("SpellAidUI_PressF1");
	m_PressF1->position = { -800.0f, -475.0f, 0.0f };
	m_PressF1->text = "Press F1 to go back";
	m_PressF1->textAlignment = TextAlignment::MID;
	m_PressF1->fontSize = 24.0f;
	m_PressF1->color = AC_WHITE;
	m_PressF1->outlineColor = AC_BLACK;

	m_BackButton = new StaticButton("Back", { 200.0f, 110.0f, 1.0f });
	m_BackButton->position = { -800.0f, -375.0f, 0.0f };

	for (int idx = 1; idx <= 3; idx++)
	{
		StaticButton* pageButton = new StaticButton(std::to_string(idx), { 125.0f, 125.0f, 1.0f });
		pageButton->position = { 575.0f + (idx - 1) * pageButton->scale.x, -450.0f, 0.0f };

		switch (idx) 
		{
			case 1: 
				pageButton->onHover = [this](Button* button)
				{
					if (!m_EffectAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png");
					}
				};
				pageButton->onPress = [this](Button* button)
				{
					if (!m_EffectAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
					}
				};
				pageButton->unHover = [this](Button* button)
		{
			if (!m_EffectAidUI->IsActive())
			{
				button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
			}
		};
				pageButton->onClick = [this](Button* button)
				{
					if (!m_EffectAidUI->IsActive())
					{
						m_EffectAidUI->SetActive(true);
						m_SpellAidUI->SetActive(false);
						m_SpellTypeAidUI->SetActive(false);
					}
				};
				break;
			case 2:
				pageButton->onHover = [this](Button* button)
				{
					if (!m_SpellAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png");
					}
				};
				pageButton->onPress = [this](Button* button)
				{
					if (!m_SpellAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
					}
				};
				pageButton->unHover = [this](Button* button)
				{
					if (!m_SpellAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
					}
				};
				pageButton->onClick = [this](Button* button)
				{
					if (!m_SpellAidUI->IsActive())
					{
						m_SpellAidUI->SetActive(true);
						m_EffectAidUI->SetActive(false);
						m_SpellTypeAidUI->SetActive(false);
					}
				};
				break;
			case 3:
				pageButton->onHover = [this](Button* button)
				{
					if (!m_SpellTypeAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_hove.png");
					}
				};
				pageButton->onPress = [this](Button* button)
				{
					if (!m_SpellTypeAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
					}
				};
				pageButton->unHover = [this](Button* button)
				{
					if (!m_SpellTypeAidUI->IsActive())
					{
						button->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_default1.png");
					}
				};
				pageButton->onClick = [this](Button* button)
				{
					if (!m_SpellTypeAidUI->IsActive())
					{
						m_SpellTypeAidUI->SetActive(true);
						m_EffectAidUI->SetActive(false);
						m_SpellAidUI->SetActive(false);
					}
				};
				break;
		}

		m_PageButtons.push_back(pageButton);
	}

	this->SetChildRenderFront(m_EffectAidUI);
	this->SetChildRenderFront(m_SpellAidUI);
	this->SetChildRenderFront(m_SpellTypeAidUI);
	this->SetChildRenderFront(m_PressF1);
	this->SetChildRenderFront(m_BackButton);
	for (int idx = 0; idx < m_PageButtons.size(); idx++)
	{
		this->SetChildRenderFront(m_PageButtons[idx]);
	}

	this->SetActive(false);
}

void PlayerAidUI::ToggleEvent(float& timeScale)
{
	if (!this->IsActive())
	{
		timeScale = 0.0f;
		this->SetActive(true);

		m_EffectAidUI->SetActive(true);
		m_SpellAidUI->SetActive(false);
		m_SpellTypeAidUI->SetActive(false);
	}
	else
	{
		timeScale = 1.0f;
		this->SetActive(false);
	}
}

void PlayerAidUI::OnUpdate(const float& dt)
{
	if (m_EffectAidUI->IsActive()) 
	{
		m_PageButtons[0]->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
	}
	else if (m_SpellAidUI->IsActive())
	{
		m_PageButtons[1]->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
	}
	else if (m_SpellTypeAidUI->IsActive())
	{
		m_PageButtons[2]->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_button_press.png");
	}
}

EffectAidUI* PlayerAidUI::GetEffectAidUI() const { return m_EffectAidUI; }
SpellAidUI* PlayerAidUI::GetSpellAidUI() const { return m_SpellAidUI; }
StaticButton* PlayerAidUI::GetBackButton() const { return m_BackButton; }