#pragma once
#include "Engine/IGameObjectManager.h"
#include "ManaRouletteNumberUI.h"
#include <array>

class ManaRouletteUI : public UIObject
{
private:
    UIObject* m_Body;
    std::function<void()> OnSpinEnd;

    std::array<ManaRouletteNumberUI*, 6> m_Numbers;

    virtual void OnUpdate(const float& dt) override;

    float m_SpinSpeed = 960.0f;
    float m_CurrentSpinSpeed = 0.0f;

    int m_SpinResult = -1;
    float m_DestinatedAngle = 0.0f;
    float m_Timer = 0.0f;
    float m_SpinTime = 2.0f;

    int m_Direction;

    void SnapRotation(const float& dt);
public:
    ManaRouletteUI(int position);

    void SetSpinResult(int n, std::function<void()> SpinEndCallback);

    void ResetRoulette();
};