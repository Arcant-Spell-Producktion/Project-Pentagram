#pragma once
#include "Engine/IGameObjectManager.h"
#include "ManaRouletteNumberUI.h"
#include <array>
#include <functional>

class ManaRouletteUI : public UIObject
{
private:
    enum RouletteState
    {
        IDLE,
        SPINNING,
        SLOWING_DOWN,
        OVERSHOOTING,
        BACKTRACKING,
        FREEZE,
        DONE
    };

    RouletteState m_State = IDLE;
    float m_OvershootAmount = 0.0f;
    float m_OvershootTarget = 0.0f;

    UIObject* m_Body;
    std::function<void()> OnSpinEnd;

    std::array<ManaRouletteNumberUI*, 6> m_Numbers;

    virtual void OnUpdate(const float& dt) override;
    void RotateRoulette(const float& dt);
    void Spin(const float& dt);
    void SlowDown(const float& dt);

    float m_SpinSpeed = 600.0f;
    float m_CurrentSpinSpeed = 0.0f;

    int m_SpinResult = -1;
    float m_DestinatedAngle = 0.0f;
    float m_SpinTimer = 0.0f;
    float m_SpinTime = 0.8f;

    float m_FreezeTimer = 0.0f;
    const float m_FreezeTime = 0.5f;

    int m_Direction;

    void OvershootRotation(const float& dt);
    void Backtrack(const float& dt);
    float lerp(float a, float b, float t);
    void FreezeRoulette();

    float AngleDifference(float angle1, float angle2);

public:
    ManaRouletteUI(int position);

    void SetRouletteNumbers(std::array<int, 6> numbers);

    void SetSpinResult(int n, std::function<void()> SpinEndCallback);

    void ResetRoulette();
};
