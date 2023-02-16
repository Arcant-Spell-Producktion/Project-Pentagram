#include "WillCompareController.h"
#include "Engine/GameStateController.h"


ParticleProperty GetCrashParticleProp()
{
    ParticleProperty particleProp;

    particleProp.position = { 0.0f, -50.0f };
    particleProp.positionVariation = { 50.0f, 150.0f };
    particleProp.colorBegin = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    particleProp.colorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
    particleProp.sizeBegin = 80.0f;
    particleProp.sizeEnd = 50.0f;
    particleProp.rotationVariation = 0.0f;
    particleProp.velocityVariation = { 300.0f, 300.0f };
    particleProp.lifeTime = 0.5f;

    return particleProp;
}

ParticleProperty GetCasterParticleProp(int caster,bool isStrong)
{
    int flip = caster == 0 ? 1 : -1;
    ParticleProperty particleProp;

    particleProp.position = { -700.0f * flip, -200.0f };

    float posVariation = !isStrong ? 0.0f : 50.0f;
    particleProp.positionVariation = { posVariation, posVariation };
    particleProp.colorBegin = caster ? 
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) : glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    particleProp.colorEnd = !isStrong ? glm::vec4(1.0f, 0.0f, 0.7f, 0.5f) : caster ?
        glm::vec4(0.0f, 0.5f, 1.0f, 1.0f) : glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);;
    particleProp.sizeBegin = !isStrong ? 50.0f : 75.0f;
    particleProp.sizeEnd = !isStrong ? 10.0f : 15.0f;
    particleProp.rotationVariation = 0.0f;
    particleProp.velocity = { (!isStrong ? 700.0f : 1800.0f) * flip, 200.0f };
    particleProp.velocityVariation = { 0.0f, 200.0f };
    particleProp.lifeTime = 1.0f;

    return particleProp;
}

bool TimerEnd(float& timer , float newTimerValue = 0)
{
    bool isEnd = timer <= 0;
    if (isEnd) timer = newTimerValue;
    return isEnd;
}

void WillCompareController::UpdateParticle()
{
    bool isStrong = true;
    m_curTime = 2.0f;

    switch (m_CompareResult)
    {
    case CasterPosition::TIED:
        m_CurrentState = CompareState::Tie;
        m_curTime = 1.0f;
        m_ParticleA->SetSpawnTime(99);
        m_ParticleB->SetSpawnTime(99);
        break;
    case CasterPosition::CasterA:
        m_CurrentState = CompareState::Push;

        m_ParticleA->baseParticle = GetCasterParticleProp(0, isStrong);
        m_ParticleA->SetSpawnTime(isStrong ? 0.001f : 0.015f);
        m_ParticleA->Emit(m_ParticleA->baseParticle);

        m_ParticleB->SetSpawnTime(99);
        m_ParticleCenter->SetSpawnTime(99);
        break;
    case CasterPosition::CasterB:
        m_CurrentState = CompareState::Push;

        m_ParticleB->baseParticle = GetCasterParticleProp(1, isStrong);
        m_ParticleB->SetSpawnTime(isStrong ? 0.001f : 0.015f);
        m_ParticleB->Emit(m_ParticleB->baseParticle);

        m_ParticleA->SetSpawnTime(99);
        m_ParticleCenter->SetSpawnTime(99);
        break;
    default:
        break;
    }
}

void WillCompareController::FadeOutParticle()
{
    m_curTime = 1.5f;
    m_ParticleA->SetSpawnTime(99);
    m_ParticleB->SetSpawnTime(99);
    m_ParticleCenter->SetSpawnTime(99);
    m_CurrentState = CompareState::Fade;
}

void WillCompareController::EndCompare()
{
    this->SetActive(false);
    OnCompareDone.Invoke(m_PlayedAnimation);
    m_CurrentState = CompareState::None;
}

WillCompareController::WillCompareController():GameObject("WillCompareController")
{
    m_CompareResult = CasterPosition::TIED;

    this->color.a = 0.0f;

    m_ParticleA = new ParticleSystem("ParticleWillA");
    m_ParticleB = new ParticleSystem("ParticleWillB");
    m_ParticleCenter = new ParticleSystem("ParticleWillCenter");

    this->SetChildRenderFront(m_ParticleA);
    this->SetChildRenderFront(m_ParticleB);
    this->SetChildRenderFront(m_ParticleCenter);

    this->SetActive(false);
    m_CurrentState = CompareState::None;

}

void WillCompareController::StartCompare(CasterPosition pos)
{
    m_CompareResult = pos;

    this->SetActive(true);

    bool isStrong = false;
    m_ParticleA->baseParticle = GetCasterParticleProp(0, isStrong);
    m_ParticleA->SetSpawnTime(isStrong ? 0.001f : 0.015f);
    m_ParticleA->Emit(m_ParticleA->baseParticle);

    m_ParticleB->baseParticle = GetCasterParticleProp(1, isStrong);
    m_ParticleB->SetSpawnTime(isStrong ? 0.001f : 0.015f);
    m_ParticleB->Emit(m_ParticleB->baseParticle);

    m_CurrentState = CompareState::Start;
    m_curTime = 1.0f;
}

void WillCompareController::OnUpdate(const float& dt)
{
    if (m_CurrentState >= CompareState::Start)
    {
        m_curTime -= dt;
        if (TimerEnd(m_curTime))
        {
            switch (m_CurrentState)
            {
            case WillCompareController::None:
                break;
            case WillCompareController::Start:
                m_curTime = 2.0f;

                m_ParticleCenter->baseParticle = GetCrashParticleProp();
                m_ParticleCenter->Emit(m_ParticleCenter->baseParticle);
                m_ParticleCenter->SetSpawnTime(0.0001f);
                m_CurrentState = CompareState::Crash;
                break;
            case WillCompareController::Crash:
                UpdateParticle();
                break;
            case WillCompareController::Push:
            case WillCompareController::Tie:
                FadeOutParticle();
                break;
            case WillCompareController::Fade:
                m_CurrentState = WillCompareController::Done;
                break;
            case WillCompareController::Done:
                EndCompare();
                break;
            default:
                break;
            }

        }
    }
}

