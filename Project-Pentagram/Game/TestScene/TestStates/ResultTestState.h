#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"

class ResultTestState : public BaseBattleState
{
private:
    float m_Timer = 0.0f;
    float m_WaitTime = 2.5f;
public:
    ResultTestState() :BaseBattleState(BattleState::ResultState) {}
    void OnBattleStateIn() override;
    void OnBattleStateUpdate(float dt) override;
    void OnBattleStateOut() override;
};
