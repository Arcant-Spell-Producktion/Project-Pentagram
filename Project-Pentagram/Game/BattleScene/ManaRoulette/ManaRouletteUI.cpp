#include "ManaRouletteUI.h"
#include <math.h>

ManaRouletteUI::ManaRouletteUI(int position) :UIObject("ManaRoulette")
{
    m_Direction = position == 0 ? 1 : -1;

    this->color.a = 0.0f;
    this->position.x -= 350.0f * m_Direction;

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

    m_Body->rotation = 360.0f;

    m_SpinResult = n;

    // Calculate the destinated angle based on the spin result and direction
    m_DestinatedAngle = m_SpinResult * 60.0f;

    if (m_Direction == 1) {
     // m_DestinatedAngle -= 60.0f;
    }
    else {
    }

    m_Body->rotation = 0.0f;
    m_SpinTimer = m_SpinTime;
    m_CurrentSpinSpeed = m_SpinSpeed;

    m_State = SPINNING;

    std::cout << "\t!!!!SPIN RESULT: " << m_Direction << " " << m_SpinResult << " " << m_DestinatedAngle << std::endl;

}


void ManaRouletteUI::ResetRoulette()
{
    for (auto num : m_Numbers)
    {
        num->SetIsUsed(false);
    }
}

void ManaRouletteUI::OnUpdate(const float& dt)
{
    if (m_State != IDLE)
    {
        RotateRoulette(dt);
    }
}

void ManaRouletteUI::RotateRoulette(const float& dt)
{
    switch (m_State)
    {
    case SPINNING:
        Spin(dt);
        break;
    case SLOWING_DOWN:
        SlowDown(dt);
        break;
    case OVERSHOOTING:
        OvershootRotation(dt);
        break;
    case BACKTRACKING:
        Backtrack(dt);
        break;
    case FREEZE:
        if (m_FreezeTimer > 0)
        {
            m_FreezeTimer -= dt;
        }
        else
        {
            m_FreezeTimer = 0;
            m_State = DONE;
        }
        break;

    case DONE:
        OnSpinEnd();
        m_State = IDLE;
        break;
    }

    m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;

    if (m_Body->rotation < 180.0f)
    {
        m_Body->rotation += 360.0f;
    }

    if (m_Body->rotation > 540.0f)
    {
        m_Body->rotation -= 360.0f;
    }
}

void ManaRouletteUI::Spin(const float& dt)
{
    m_SpinTimer -= dt;

    if (m_SpinTimer <= 0)
    {
        m_State = SLOWING_DOWN;
        std::cout << m_Direction << " -> SLOW\n";

    }
    else
    {
        m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;
    }
}
void ManaRouletteUI::SlowDown(const float& dt)
{
    float targetSpeed = m_SpinSpeed * 0.2f;
    m_CurrentSpinSpeed = lerp(m_CurrentSpinSpeed, targetSpeed, dt * 2.0f);

    m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;

    float angleDiff = AngleDifference(m_Body->rotation, m_DestinatedAngle);

    if (angleDiff <= 15.0f && m_CurrentSpinSpeed <= targetSpeed * 1.1f)
    {
        m_OvershootTarget = m_DestinatedAngle + (rand() % 20 - 10) * m_Direction;
        m_State = OVERSHOOTING;

        std::cout << m_Direction << " -> OVERSHOOT\n";
    }
}

void ManaRouletteUI::OvershootRotation(const float& dt)
{
    float targetSpeed = m_SpinSpeed * 0.1f;
    m_CurrentSpinSpeed = lerp(m_CurrentSpinSpeed, targetSpeed, dt * 2.0f);
    m_Body->rotation -= m_CurrentSpinSpeed * m_Direction * dt;

    float angleDiff = AngleDifference(m_Body->rotation, m_OvershootTarget);
    if (angleDiff <= 5.0f && m_CurrentSpinSpeed <= targetSpeed * 1.1f)
    {
        m_State = BACKTRACKING;
        std::cout << m_Direction << " -> BACK\n";

    }
}

void ManaRouletteUI::Backtrack(const float& dt)
{
    float targetSpeed = m_SpinSpeed * 0.05f;

    m_CurrentSpinSpeed = lerp(m_CurrentSpinSpeed,targetSpeed , dt * 2);

    m_Body->rotation -= m_CurrentSpinSpeed * -m_Direction * dt;

    float angleDiff = AngleDifference(m_Body->rotation, m_DestinatedAngle);
    if (angleDiff <= 5.0f || (int)m_CurrentSpinSpeed == targetSpeed)
    {
        FreezeRoulette();
        std::cout << m_Direction << " -> FREZE\n";

    }
}

void ManaRouletteUI::FreezeRoulette()
{
    std::cout << "ACTUAL END ROT" << m_Direction << " " << fmod(m_Body->rotation,360.0f) << "\n";
    m_CurrentSpinSpeed = 0.0f;
    //m_Body->rotation = m_DestinatedAngle;
    m_Numbers[m_SpinResult]->SetIsUsed(true);
    m_SpinResult = -1;
    m_SpinTimer = 0;

    m_FreezeTimer = m_FreezeTime;
    m_State = FREEZE;
}

float ManaRouletteUI::AngleDifference(float angle1, float angle2)
{
    float diff = fmod(angle1 - angle2 + 360.0f, 360.0f);
    if (diff > 180.0f)
    {
        diff = 360.0f - diff;
    }
    return diff;
}

float ManaRouletteUI::lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
