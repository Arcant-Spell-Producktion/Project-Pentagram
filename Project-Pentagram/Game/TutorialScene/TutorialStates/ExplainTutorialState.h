#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"
#include "Game/Objects/TextBox.h"

class ExplainTutorialState : public BaseBattleState
{
private:
    int m_CurrentText;
    std::vector<std::string> m_explainTexts;

    TextBox* m_Texts;
public:
    ExplainTutorialState() :BaseBattleState(BattleState::ExplainState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
