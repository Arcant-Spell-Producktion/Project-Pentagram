#include "CasterStatUI.h"

CasterStatUI::CasterStatUI(PlayerData* playerData)
	: UIObject("CasterStatUI")
{
	this->scale = { 520.0f, 200.0f, 1.0f };
	this->position = { -(WINDOW_WIDTH / 2.0f) + (this->scale.x / 2.0f),
						-(WINDOW_HEIGHT / 2.0f) + (this->scale.y / 2.0f), 0.0f };

	switch (playerData->Element())
	{
		case Element::Earth: this->color = { 0.58f, 0.3f, 0.0f, 1.0f }; break;
		case Element::Fire: this->color = { 1.0f, 0.39f, 0.28f, 1.0f }; break;
		case Element::Water: this->color = { 0.0f, 0.75f, 1.0f, 1.0f }; break;
		case Element::Wind: this->color = { 0.68f, 1.0f, 0.18f, 1.0f }; break;
	}

	const float offset = 10.0f;
	m_CasterProfile = new UIObject("CasterProfile");
	m_CasterProfile->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_CasterProfile->scale = { 180.0f, 180.0f, 1.0f };
	m_CasterProfile->position = { -(this->scale.x / 2.0f) + (m_CasterProfile->scale.x / 2.0f) + offset, 0.0f, 0.0f };
	this->SetChildRenderFront(m_CasterProfile);

	m_ManaWheelUI = new UIObject("ManaWheelUI");
	m_ManaWheelUI->SetTexture("Sprites/UI/Game/ui_game_roulette_body.png");
	m_ManaWheelUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_ManaWheelUI->scale = { 80.0f, 80.0f, 1.0f };
	m_ManaWheelUI->position = { 0.0f, (this->scale.y / 2.0f) - (m_ManaWheelUI->scale.y / 2.0f) - offset, 0.0f };
	this->SetChildRenderFront(m_ManaWheelUI);

	// Mana Object
	m_ManaUI = new UIObject("ManaUI");
	m_ManaUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_ManaUI->scale = { 200.0f, 100.0f, 1.0f };
	m_ManaUI->position = { (this->scale.x / 2.0f) - (m_ManaUI->scale.x / 2.0f),
							(this->scale.y / 2.0f) - (m_ManaUI->scale.y / 2.0f), 0.0f };
	this->SetChildRenderFront(m_ManaUI);

	m_ManaTextUI = new TextObject("ManaUI_Text");
	std::string manaText;
	for (int idx = 0; idx < 6; idx++)
	{
		manaText += std::to_string(playerData->Stat().ManaWheel[idx]);
		if (idx < 5)
		{
			manaText += "/";
		}
	}
	m_ManaTextUI->text = manaText;
	m_ManaTextUI->fontSize = 36.0f;
	m_ManaTextUI->textAlignment = TextAlignment::MID;
	m_ManaTextUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_ManaTextUI->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_ManaUI->SetChildRenderFront(m_ManaTextUI);

	// Hp Object
	m_HPUI = new UIObject("HP_UI");
	m_HPUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_HPUI->scale = { 300.0f, 80.0f, 1.0f };
	m_HPUI->position = { (this->scale.x / 2.0f) - (m_HPUI->scale.x / 2.0f) - offset,
							-(this->scale.y / 2.0f) + (m_HPUI->scale.y / 2.0f) + offset, 0.0f };
	this->SetChildRenderFront(m_HPUI);

	m_HPTextUI = new TextObject("HPTextUI");
	m_HPTextUI->text = std::to_string(playerData->Stat().CurrentHealth) + "/" + std::to_string(playerData->Stat().MaxHealth);
	m_HPTextUI->fontSize = 36.0f;
	m_HPTextUI->textAlignment = TextAlignment::MID;
	m_HPTextUI->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_HPTextUI->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_HPUI->SetChildRenderFront(m_HPTextUI);
}