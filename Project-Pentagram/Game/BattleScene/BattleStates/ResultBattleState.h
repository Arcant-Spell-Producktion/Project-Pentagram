#pragma once
#include "BaseBattleState.h"

class ResultBattleState : public BaseBattleState
{
private:
    float m_Timer = 0.0f;
    float m_WaitTime = 2.5f;

    bool m_IsAlive = true;
public:
    ResultBattleState() :BaseBattleState(BattleState::ResultState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
