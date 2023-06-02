#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"
#include "Game/Objects/TextBox.h"
#include "Game/GameData/TutorialData/TutorialNodes/TutorialEvent.h"

#include "Engine/GameStateController.h"

class ExplainTutorialState : public BaseBattleState
{
private:
    int m_CurrentEvent;
    TutorialEvents m_TutorialStep;

    TextBox* m_Texts;

    bool m_IsClickAble = false;

    void UpdateEvent();
    void OnTextClick();
public:
    ExplainTutorialState() :BaseBattleState(BattleState::ExplainState) 
    {
        m_Texts = GameStateController::GetInstance().currentScene->CreateObject(new TextBox(""));
        m_Texts->SetActive(false);
        BattleManager::GetInstance().Data.Texts = m_Texts;
    }
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;
};
