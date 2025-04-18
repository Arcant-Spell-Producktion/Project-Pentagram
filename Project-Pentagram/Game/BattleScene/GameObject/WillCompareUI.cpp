#include "WillCompareUI.h"

WillCompareUI::WillCompareUI(int trackIndex)
	: UIObject("WillCompareUI")
{
    this->color = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_PlayerWill = new TextObject("m_PlayerWill" + std::to_string(trackIndex));
    m_PlayerWill->position = { -30.0f, 0.0f, 0.0f };
    m_PlayerWill->color = AC_YELLOW;
    m_PlayerWill->outlineColor = AC_BLACK;
    m_PlayerWill->textAlignment = TextAlignment::MID;
    m_PlayerWill->fontSize = WillCompareTextSize;

	m_EnemyWill = new TextObject("m_PlayerWill" + std::to_string(trackIndex));
    m_EnemyWill->position = { 30.0f, 0.0f, 0.0f };
    m_EnemyWill->color = AC_MAGENTA;
    m_EnemyWill->outlineColor = AC_BLACK;
    m_EnemyWill->textAlignment = TextAlignment::MID;
    m_EnemyWill->fontSize = WillCompareTextSize;

    this->SetChildRenderFront(m_PlayerWill);
    this->SetChildRenderFront(m_EnemyWill);
}

void WillCompareUI::OnUpdate(const float& dt)
{
    TextObject* greaterWillObject = GetGreaterWillObject();
    if (greaterWillObject)
    {
        UpdateTextSize(greaterWillObject, dt);
    }
}

void WillCompareUI::UpdateTextWillValue(const std::vector<SpellIconUI*>& icons)
{
    m_ExpandDir = 1;

    m_PlayerWillValue = 0;
    m_EnemyWillValue = 0;

    for (int i = 0; i < icons.size(); i++)
    {
        SpellIconUI* icon = icons[i];
        if (icon->SpellDetail->SpellOwner == CasterPosition::CasterA)
        {
            m_PlayerWillValue += icon->SpellDetail->SelectedWill;
        }
        else if (icon->SpellDetail->SpellOwner == CasterPosition::CasterB)
        {
            m_EnemyWillValue += icon->SpellDetail->SelectedWill;
        }
    }

    if (m_PlayerWillValue == 0 && m_EnemyWillValue == 0)
    {
        m_PlayerWill->SetActive(false);
        m_EnemyWill->SetActive(false);
    }
    else
    {
        m_PlayerWill->SetActive(true);
        m_EnemyWill->SetActive(true);

        m_PlayerWill->text = std::to_string(m_PlayerWillValue);
        m_EnemyWill->text = std::to_string(m_EnemyWillValue);
    }
}
void WillCompareUI::ResetWillCompareUI()
{
    m_PlayerWillValue = 0;
    m_EnemyWillValue = 0;

    m_PlayerWill->SetActive(false);
    m_EnemyWill->SetActive(false);
}


TextObject* WillCompareUI::GetGreaterWillObject()
{
    if (m_PlayerWillValue > m_EnemyWillValue) { return m_PlayerWill; }
    else if (m_PlayerWillValue < m_EnemyWillValue) { return m_EnemyWill; }
    else { return nullptr; }
}

void WillCompareUI::UpdateTextSize(TextObject* casterWillUI, const float& dt)
{
    if (casterWillUI->fontSize < WillCompareTextSize || casterWillUI->fontSize > WillCompareMaxTextSize)
    {
        m_ExpandDir *= -1;

        if (casterWillUI->fontSize <= WillCompareTextSize) { casterWillUI->fontSize = WillCompareTextSize; }
        else if(casterWillUI->fontSize >= WillCompareMaxTextSize) { casterWillUI->fontSize = WillCompareMaxTextSize; }
    }

    casterWillUI->fontSize += 10.0f * dt * m_ExpandDir;
}