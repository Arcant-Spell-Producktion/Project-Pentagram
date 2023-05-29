#include "MapInfoUI.h"

const std::string earthMapDescription = R"(Earth stage: A city of stone and science,
found in a cavern and fill with machinery 
fueled with magic led by Tierra
Tarrencrest witch of the moving plateau.)";

const std::string fireMapDescription = R"(Fire stage: A city of flame surrounded
by lava and volcano. Once guarded by 
Helia Hino the witch of undying flame.)";

const std::string waterMapDescription = R"(Water stage: An Under water city locate
under the oceanic island maintained by
Seina Aquarone witch of the deep sea.)";

const std::string windMapDescription = R"(Wind stage: A city of wind. Floating
isolated land of serenity and breeze
overseen by Fumi Ventis witch of 
wailing wind)";

const std::string corruptMapDescription = R"(Corrupts stage: Once a small deserted
island fill with vegetation, now center
of corruptions that plague this land as
the source of corruptions lies within.)";

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
	m_MapInfoText->isVCenterAlignment = true;
	m_MapInfoText->fontSize = 18.5f;
	m_MapInfoText->textAlignment = TextAlignment::LEFT;
	m_MapInfoText->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_MapInfoText->outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_MapEnterButton = new StaticButton("Enter", { 200.0f, 90.0f, 1.0f });
	m_MapEnterButton->position = { (m_InfoBG->scale.x / 2.0f) - (m_MapEnterButton->scale.x / 2.0f) - 7.5f, 0.0f, 1.0f };

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
			this->position = { 625.0f, -350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Earth/stage_earth_background.png");
			this->m_MapInfoText->text = earthMapDescription;
			this->SetActive(true);
			break;

		case Element::Fire:	
			this->position = { -625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Fire/stage_fire_background.png");
			this->m_MapInfoText->text = fireMapDescription;
			this->SetActive(true);
			break;

		case Element::Water:
			this->position = { 625.0f, 350.0f, 0.0f };
			this->SetTexture("Sprites/Stage/Water/stage_water_background.png");
			this->m_MapInfoText->text = waterMapDescription;
			this->SetActive(true);
			break;

		case Element::Wind:
            this->position = { -625.0f, -350.0f, 0.0f };
            this->SetTexture("Sprites/Stage/Wind/stage_wind_background.png");
			this->m_MapInfoText->text = windMapDescription;
            this->SetActive(true);
			break;

		case Element::Corrupt:
            this->position = { -350.0f, 350.0f, 0.0f };
            this->SetTexture("Sprites/Stage/Corrupt/stage_corrupt_background.png");
			this->m_MapInfoText->text = corruptMapDescription;
            this->SetActive(true);
            break;
	}
}