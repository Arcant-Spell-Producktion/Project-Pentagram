#include "SpellAidUI.h"

SpellAidUI::SpellAidUI() : UIObject("SpellAidUI")
{
	this->scale = { 1920.0f, 1080.0f, 1.0f };
	this->color = AC_BLACK;

	m_Header = new TextObject("SpellAidUI_Header");
	m_Header->position = { 0.0f, 450.0f, 0.0f };
	m_Header->text = "Specials Spell List";
	m_Header->textAlignment = TextAlignment::MID;
	m_Header->fontSize = 96.0f;
	m_Header->color = AC_WHITE;
	m_Header->outlineColor = AC_BLACK;
	this->SetChildRenderFront(m_Header);

	for (int idx = 0; idx < 4; idx++)
	{
		switch (idx)
		{
			case 0: m_SpellList[idx] = new SpellObject(Element::Earth, 7, idx); break;
			case 1: m_SpellList[idx] = new SpellObject(Element::Earth, 5, idx); break;
			case 2: m_SpellList[idx] = new SpellObject(Element::Earth, 6, idx); break;
			case 3: m_SpellList[idx] = new SpellObject(Element::Wind, 6, idx); break;
		}

		m_SpellList[idx]->position = m_SpellPositionList[idx];
		this->SetChildRenderFront(m_SpellList[idx]);
	}
}