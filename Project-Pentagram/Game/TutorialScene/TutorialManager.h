#pragma once
#include <map>
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/BattleScene/IBattleController.h"
#include "Game/TutorialScene/TutorialStates/TutorialStateModel.h"
#include "Utilities/Singleton.h"

class TutorialManager : public Singleton<TutorialManager>, virtual public IBattleController<TutorialState>
{
private:
    TutorialState m_CurrentState = TutorialState::SetupState;
    std::map<TutorialState, BaseTutorialState*> m_TutorialStates;

public:
    BattleSceneData Data;

    void SetBattleState(TutorialState state) override;

    BaseTutorialState* GetBattleStates() override { return m_TutorialStates[m_CurrentState]; }

    void Init(IGameObjectManager* scene) override;

    void StartBattle() override;
    void SwapCaster() override;
    void EndBattle() override {(TutorialState::ResultState); }

    void UpdateDisplaySpellDetail(CasterPosition position,CastSpellDetail* spell = nullptr, bool isMainData = false, glm::vec3 IconPos = {0,0,0});


    ~TutorialManager() override;
};
