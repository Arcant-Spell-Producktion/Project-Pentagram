#include "ManaRouletteUI.h"
#include <math.h>

ManaRouletteUI::ManaRouletteUI(int position) :UIObject("ManaRoulette")
{
    m_Direction = position == 0 ? 1 : -1;

    this->color.a = 0.0f;
    this->position.x -= 400.0f * m_Direction;

    m_Body = new UIObject("ManaRoulette_Body");
    m_Body->SetTexture("Sprites/UI/Game/ui_game_roulette_body.png");
    m_Body->scale = { 426.0f,426.0f,1.0f };
    this->SetChildRenderBack(m_Body);

	for (int i = 0; i < 6; ++i)
	{
		ManaRouletteNumberUI* num = new ManaRouletteNumberUI(i);
		num->SetNumberByValue(i + 1);
		float theta = 2.0f * 3.142526f * (i / 6.0f);
		theta += 1.571428f * m_Direction;
		float radius = 120.0f;
		num->position = { radius * sinf(theta),radius * cosf(theta),0.0f };
		num->rotation -= i * 60.0f;
		//num->position = { 50.0f * i,0.0f,0.0f };
		m_Numbers[i] = num;
        m_Body->SetChildRenderFront(num);

	}


	UIObject* point = new UIObject("ManaRoulette_Point");
	point->SetTexture("Sprites/UI/Game/ui_game_roulette_pointer.png");
	point->scale = { 100.0f * m_Direction,100.0f,1.0f };
	point->position.x += 200.0f * m_Direction;
	this->SetChildRenderFront(point);
}

void ManaRouletteUI::SetRouletteNumbers(std::array<int, 6> numbers)
{

    for (int i = 0; i < 6; ++i)
    {
        m_Numbers[i]->SetNumberByValue(numbers[i]);
    }
}

void ManaRouletteUI::SetSpinResult(int n, std::function<void()> callback)
{
    OnSpinEnd = callback;

    m_SpinResult = n;
    m_DestinatedAngle = m_SpinResult * 60.0f;
    m_Body->rotation = 0.0f;
    m_Timer = m_SpinTime;
    m_CurrentSpinSpeed = m_SpinSpeed;
}

void ManaRouletteUI::ResetRoulette()
{
    for (auto num:m_Numbers)
    {
        num->SetIsUsed(false);
    }
}


void ManaRouletteUI::OnUpdate(const float& dt)
{
    if (m_Timer > 0 || m_SpinResult != -1)
    {
        m_Timer -= dt;

        if (m_Timer <= 0)
        {
            SnapRotation(dt);
        }
        else
        {
            m_CurrentSpinSpeed = m_SpinSpeed;
            m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;
        }
    }
}


void ManaRouletteUI::SnapRotation(const float& dt)
{
    int snapArea = 5;
    int laps = static_cast<int>(m_Body->rotation / 360.0f);
    int resultAngle = (360 * laps) - m_DestinatedAngle;
    float distant = std::fabs(m_Body->rotation - resultAngle);

    bool doSnap = distant < snapArea;
    if (doSnap && m_CurrentSpinSpeed < 100.0f)
    {
        m_CurrentSpinSpeed = 0.0f;
        m_Body->rotation = m_DestinatedAngle;
        m_Timer = 0;
        m_Numbers[m_SpinResult]->SetIsUsed(true);
        m_SpinResult = -1;
        OnSpinEnd();
    }
    else
    {
        m_CurrentSpinSpeed -= m_SpinSpeed * distant / 360.0f *dt;
        m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;
    }
}



