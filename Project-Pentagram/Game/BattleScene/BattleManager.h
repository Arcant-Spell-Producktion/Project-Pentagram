#pragma once
#include <map>
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/BattleSceneData.h"
#include "Game/BattleScene/IBattleController.h"
#include "Game/BattleScene/BattleStates/BattleStateModel.h"
#include "Utilities/Singleton.h"

class BattleManager : public Singleton<BattleManager>, virtual public IBattleController<BattleState>
{
private:
    BattleState m_CurrentState = BattleState::SetupState;
    std::map<BattleState, BaseBattleState*> m_BattleStates;

public:
    BattleSceneData Data;

    void SetBattleState(BattleState state) override;

    BaseBattleState* GetBattleStates() override { return m_BattleStates[m_CurrentState]; }

    void Init(IGameObjectManager* scene) override;

    void StartBattle() override;
    void SwapCaster() override;
    void EndBattle() override { SetBattleState(BattleState::ResultState); }

    void UpdateDisplaySpellDetail(CasterPosition position,CastSpellDetail* spell = nullptr, bool isMainData = false, glm::vec3 IconPos = {0,0,0});


    ~BattleManager() override;
};
