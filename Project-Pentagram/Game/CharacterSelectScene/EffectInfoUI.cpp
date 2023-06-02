#include "EffectInfoUI.h"

EffectInfoUI::EffectInfoUI()
	: UIObject("EffectInfoUI")
{
	this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_EffectIcon = new UIObject("Effect_Icon");
	m_EffectIcon->scale = { 80.0f, 80.0f, 1.0f };
	this->SetChildRenderFront(m_EffectIcon);

	m_EffectInfo = new TextObject("Effect_Info");
	m_EffectInfo->fontSize = 24.0f;
	m_EffectInfo->color = AC_WHITE;
	m_EffectInfo->outlineColor = AC_BLACK;
	this->SetChildRenderFront(m_EffectInfo);
}

void EffectInfoUI::SetFitWithBorder(const glm::vec3 borderScale)
{
	const float offset = 50.0f;
	m_EffectIcon->position.x = (-borderScale.x / 2.0f + m_EffectIcon->scale.x / 2.0f) + offset;

	m_EffectInfo->position = { (m_EffectIcon->position.x + m_EffectIcon->scale.x / 2.0f) + offset / 2.0f, 25.0f, 0.0f };
}
void EffectInfoUI::SetEffectIconTexture(const std::string& filePath)
{
	m_EffectIcon->SetTexture(filePath);
}
void EffectInfoUI::SetEffectIconIndex(const glm::ivec2& index)
{
	m_EffectIcon->SetSpriteByIndex(index.x, index.y);
}
void EffectInfoUI::SetEffectInfo(const std::string& info)
{
	m_EffectInfo->text = info;
}

TextObject* EffectInfoUI::GetEffectInfoText() const
{
	return m_EffectInfo;
}