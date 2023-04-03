#include "MapInfoUI.h"

MapInfoUI::MapInfoUI()
	: UIObject("MapInfoUI")
{
	this->position = { 0.0f, 0.0f, 0.0f };
	this->scale = { 600.0f, 600.0f * (9.0f / 16.0f), 1.0f };
	
	m_InfoBG = new UIObject("InfoBG");
	m_InfoBG->color = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_InfoBG->scale = { this->scale.x, 100.0f, 1.0f };
	m_InfoBG->position = { 0.0f, (this->scale.y / 2.0f) - (m_InfoBG->scale.x / 2.0f), 0.0f };

	m_MapInfoText = new TextObject("MapInfoText");
	m_MapInfoText->position = { -(m_InfoBG->scale.x / 2.0f) + 10.0f, 0.0f, 0.0f };
	m_MapInfoText->text = "Map Description";
	m_MapInfoText->fontSize = 20.0f;
	m_MapInfoText->textAlignment = TextAlignment::LEFT;
	m_MapInfoText->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_MapInfoText->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_MapEnterButton = new Button("MapEnterButton");
	m_MapEnterButton->scale = { 175.0f, 80.0f, 1.0f };
	m_MapEnterButton->position = { (m_InfoBG->scale.x / 2.0f) - (m_MapEnterButton->scale.x / 2.0f) - 10.0f, 0.0f, 1.0f };
	m_MapEnterButton->textObject.text = "Enter";

	m_InfoBG->SetChildRenderFront(m_MapInfoText);
	m_InfoBG->SetChildRenderFront(m_MapEnterButton);

	this->SetChildRenderFront(m_InfoBG);
	this->SetActive(false);
}

void MapInfoUI::SetMapInfo(const Element::Type& element)
{
	switch (element)
	{
		case Element::Earth:
			//Set Earth Stage Background
			break;

		case Element::Fire:	
			this->position = { -625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Fire/stage_fire_background.png");
			this->SetActive(true);
			break;

		case Element::Water:
			this->position = { 625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Water/stage_water_background.png");
			this->SetActive(true);
			break;

		case Element::Wind:
			//Set Wind Stage Background
			break;
	}
}