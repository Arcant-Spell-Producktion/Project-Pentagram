#pragma once
#include "Engine/IGameObjectManager.h"
#include <Game/GameData/CasterData/CasterPosition.h>


class WillCompareController : public GameObject
{
private:
    enum CompareState
    {
        None = 0,
        Start = 1,
        Crash,
        Push,
        Tie,
        Fade,
        Done
    };

    CompareState m_CurrentState = CompareState::None;

    CasterPosition m_CompareResult;

    ParticleSystem* m_ParticleA = nullptr;
    ParticleSystem* m_ParticleB = nullptr;
    ParticleSystem* m_ParticleCenter = nullptr;

    float m_curTime = 0.0f;

    bool m_PlayedAnimation = false;

    void UpdateParticle();
    void FadeOutParticle();
    void EndCompare();
public:
    Event<bool> OnCompareDone;

    WillCompareController();

    void OnUpdate(const float& dt) override;

    void StartCompare(CasterPosition pos);
};