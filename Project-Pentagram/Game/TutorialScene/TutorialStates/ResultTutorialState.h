#pragma once
#include "BaseTutorialState.h"

class ResultTutorialState : public BaseTutorialState
{
private:
    float m_Timer = 0.0f;
    float m_WaitTime = 2.5f;
public:
    ResultTutorialState() :BaseTutorialState(TutorialState::ResultState) {}
    void OnBattleStateIn() override;
    void OnBattleStateUpdate(float dt) override;
    void OnBattleStateOut() override;
};
